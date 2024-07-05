#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;

/// @brief Function to print all packages in a given town
/// @param t The Town
void print_all_packages(town t) {
	// Print the town name
    printf("%s:\n", t.name);

	// Loop on all available offices
    for (int office = 0; office < t.offices_count; office++) {
		// Print the office number
        printf("\t%d:\n", office);

		// Loop on all available packages
        for (int package = 0; package < t.offices[office].packages_count; package++) {
			// Print the id of the package
            printf("\t\t%s\n", t.offices[office].packages[package].id);
        }
    }
}

/// @brief Function to send all acceptable packages from a source post office to a target post office
/// @param source town source
/// @param source_office_index twon source index
/// @param target town target
/// @param target_office_index twon target index
void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
	// Pointers 'src' and 'tgt' are initialized to point to the source and target post offices respectively
	post_office* src = (source->offices) + source_office_index;
	post_office* tgt = (target->offices) + target_office_index;

	// An array 'temp_package' is created to temporarily store packages that meet the weight criteria
	package temp_package[src->packages_count];
	// 'tem_package_size' is used to keep track of the number of packages in 'temp_package'
	int tem_package_size = 0;

	// Iterate over all packages in the source post office
	for (int outer_pkg_counter = 0; outer_pkg_counter < src->packages_count; /*Conditional increament*/) {
		// Filtering Packages: If a package's weight falls within the acceptable range of the target post office
		if ((((src->packages[outer_pkg_counter]).weight) >= (tgt->min_weight)) && (((src->packages[outer_pkg_counter]).weight) <= (tgt->max_weight))) {
			// Moving Packages: Adding to 'temp_package'
			temp_package[tem_package_size++] = (src->packages[outer_pkg_counter]);
			// Removing from the source post office by shifting the remaining packages in the array
			for (int inner_pkg_counter = outer_pkg_counter; inner_pkg_counter < ((src->packages_count) - 1); inner_pkg_counter++) {
				src->packages[inner_pkg_counter] = src->packages[inner_pkg_counter + 1];
			}
			// Decreament source packages count after removing them
			(src->packages_count)--;
		} else {
			// The Weight NOT falls within the acceptable range of the target post office
			outer_pkg_counter++;
		}
	}

	// The target post office's package array is reallocated to accommodate the new packages
	tgt->packages = realloc((tgt->packages), ((tgt->packages_count) + tem_package_size) * sizeof(package));

	// The packages stored in 'temp_package' are added to the target post office's package array
	for (int tgt_counter = 0; tgt_counter < tem_package_size; tgt_counter++) {
		tgt->packages[(tgt->packages_count)++] = temp_package[tgt_counter];
	}
}

/// @brief Function to find the town with the most number of packages
/// @param towns Array of twons
/// @param towns_count Number of twons
/// @return twon struct
town town_with_most_packages(town* towns, int towns_count) {
	// The function initializes 'max_town' to the first town in the array and 'max_packages' to 0
	town max_twon = *towns;
	int max_packages = 0;

	// The Loop calculates the total number of packages in the first town by iterating through its post offices
	for (int office_counter = 0; office_counter < (towns->offices_count); office_counter++) {
		max_packages += towns->offices[office_counter].packages_count;
	}

	// Then moves to the next town and decrements 'towns_count'
	towns++;
	towns_count--;

	// For each remaining town, the Loop calculates the total number of packages
	while (towns_count--) {
		int current_packages = 0;

		// The Loop calculates the total number of packages in the currnt town by iterating through its current post offices
		for (int current_office_counter = 0; current_office_counter < (towns->offices_count); current_office_counter++) {
			current_packages += towns->offices[current_office_counter].packages_count;
		}

		// If the current town has more packages than the previous maximum, the function updates 'max_packages' and 'max_town'
		if (current_packages > max_packages) {
			max_packages = current_packages;
			max_twon = *towns;
		}
		
		// Moving to the next town in the array
		towns++;
	}

	// After iterating through all the towns, the function returns the town with the most packages
	return max_twon;
}

/// @brief Function to find a town by name
/// @param towns Array of towns
/// @param towns_count Numbre of towns
/// @param name The name string to search on
/// @return Town if available or null if not
town* find_town(town* towns, int towns_count, char* name) {
	// Loop on all towns
    while (towns_count--) {
		// Search on the town by comparing its name with used name to search
        if (!strcmp((towns->name), name)) {
            return towns;
        }
        towns++;
    }
	// No town found
    return NULL;
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}