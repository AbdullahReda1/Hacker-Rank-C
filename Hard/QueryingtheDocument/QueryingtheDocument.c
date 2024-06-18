#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

// Return the k-th word in the m-th sentence of the n-th paragraph
char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n - 1][m - 1][k - 1];
}

// Return the k-th sentence in the m-th paragraph
char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m - 1][k - 1];
}

// Return the k-th paragraph
char*** kth_paragraph(char**** document, int k) {
    return document[k - 1];
}

// Helper function to insert a character into a word, resizing the word as needed
void insert_char(char** word, int* word_len, char ch) {
    (*word_len)++;
    *word = realloc(*word, (*word_len) * sizeof(char));
    *word[*word_len - 1] = ch;
}

// Function to check if a character is whitespace
int is_whitespace(char ch) {
    return (ch == ' ');
}

// Function to trim leading whitespace characters
void trim_whitespace(char* text, int* character) {
    while (is_whitespace(text[*character])) {
        (*character)++;
    }
}

// Function to check if a character is a valid text character
int is_text(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// Function to check if a character is a sentence terminator (period)
int is_sentence_terminator(char ch) {
    return (ch == '.');
}

// Function to check if a character is a paragraph terminator (newline or null terminator)
int is_paragraph_terminator(char ch) {
    return ((ch == '\n') || (ch == '\0'));
}

// Function to get the next character in the text and increment the index
char next_character(char* text, int* character) {
    return (text[(*character)++]);
}

// Function to parse the next word from the text
char* next_word(char* text, int* character) {
    
}

// Function to parse the next sentence from the text
char** next_sentence(char* text, int* character) {
    
}

// Function to parse the next paragraph from the text
char*** next_paragraph(char* text, int* character) {
    
}

// Function to parse the entire document from the text
char**** get_document(char* text) {
    
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}
