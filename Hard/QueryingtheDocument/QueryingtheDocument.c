#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>

#define MAX_CHARACTERS      1005
#define MAX_PARAGRAPHS      5
#define DEFAULT_LEN         8

/// @brief Return the k-th word in the m-th sentence of the n-th paragraph
/// @param document the document
/// @param k the words
/// @param m the sentences
/// @param n the paragraphs
/// @return pointer to char
char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n - 1][m - 1][k - 1];
}

/// @brief Return the k-th sentence in the m-th paragraph
/// @param document the document
/// @param k the sentences
/// @param m the paragraphs
/// @return pointer to pointer to char
char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m - 1][k - 1];
}

/// @brief Return the k-th paragraph
/// @param document the document
/// @param k the paragraphs
/// @return pointer to pointer to pointer to char
char*** kth_paragraph(char**** document, int k) {
    return document[k - 1];
}

/// @brief Helper function to insert a character into a word, resizing the word as needed
/// @param word pointer to pointer to char
/// @param word_len pointer to int
/// @param ch the character
void insert_char(char** word, int* word_len, char ch) {
    /* These lines are important, also the '()' more important */
    (*word_len)++;
    (*word) = realloc(*word, sizeof(char) * (*word_len));
    (*word)[*word_len - 1] = ch;
}

/// @brief Function to check if a character is whitespace
/// @param ch the character
/// @return boolean
int is_whitespace(char ch) {
    return (ch == ' ');
}

/// @brief Function to trim leading whitespace characters
/// @param text pointer to char
/// @param character pointer to int
void trim_whitespace(char* text, int* character) {
    while (is_whitespace(text[*character])) {
        (*character)++;
    }
}

/// @brief Function to check if a character is a valid text character
/// @param ch the character
/// @return boolean
int is_text(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

/// @brief Function to check if a character is a sentence terminator (period)
/// @param ch the character
/// @return boolean
int is_sentence_terminator(char ch) {
    return (ch == '.');
}

/// @brief Function to check if a character is a paragraph terminator (newline or null terminator)
/// @param ch the character
/// @return boolean
int is_paragraph_terminator(char ch) {
    return ((ch == '\n') || (ch == '\0'));
}

/// @brief Function to get the next character in the text and increment the index
/// @param text pointer to char
/// @param character pointer to int
/// @return **char** - the character
char next_character(char* text, int* character) {
    return (text[(*character)++]);
}

/// @brief Function to parse the next word from the text
/// @param text pointer to char
/// @param character pointer to int
/// @return **pointer to char** - the word
char* next_word(char* text, int* character) {
    char* word = malloc(DEFAULT_LEN * sizeof(char));    // Allocate initial memory for the word
    int word_size = 0;                                  // Initialize word size

    // Loop through characters until a non-text character is encountered
    while (is_text(text[*character])) {
        char ch = next_character(text, character);      // Get the next character
        insert_char(&word, &word_size, ch);             // Insert the character into the word
    }
    
    insert_char(&word, &word_size, '\0');               // Null-terminate the word
    return word;
}

/// @brief Function to parse the next sentence from the text
/// @param text pointer to char
/// @param character pointer to int
/// @return **pointer to pointer to char** - the sentence
char** next_sentence(char* text, int* character) {
    char** sentence = malloc(DEFAULT_LEN * sizeof(char*));                  // Allocate initial memory for the sentence
    int sentence_len = 0;                                                   // Initialize sentence length
    
    // Loop through characters until a sentence terminator is encountered
    while (!is_sentence_terminator(text[*character])) {
        trim_whitespace(text, character);                                   // Trim leading whitespace
        char* word = next_word(text, character);                            // Parse the next word

        sentence_len++;
        sentence = realloc(sentence, sentence_len * sizeof(char*));         // Resize the sentence array
        sentence[sentence_len - 1] = word;                                  // Add the word to the sentence
    }
    
    next_character(text, character);                                        // Move past the period
    return sentence;
}

/// @brief Function to parse the next paragraph from the text
/// @param text pointer to char
/// @param character pointer to int
/// @return **pointer to pointer to pointer to char** - the paragraph
char*** next_paragraph(char* text, int* character) {
    char*** paragraph = malloc(DEFAULT_LEN * sizeof(char**));                 // Allocate initial memory for the paragraph
    int paragraph_len = 0;                                                    // Initialize paragraph length
    
    // Loop through characters until a paragraph terminator is encountered
    while (!is_paragraph_terminator(text[*character])) {
        char** sentence = next_sentence(text, character);                     // Parse the next sentence

        paragraph_len++;
        paragraph = realloc(paragraph, paragraph_len * sizeof(char**));       // Resize the paragraph array
        paragraph[paragraph_len - 1] = sentence;                              // Add the sentence to the paragraph
    }
    
    return paragraph;
}

/// @brief Function to parse the entire document from the text
/// @param text pointer to char
/// @return **pointer to pointer to pointer to pointer to char** - the document
char**** get_document(char* text) {
    char**** document = malloc(DEFAULT_LEN * sizeof(char***));          // Allocate initial memory for the document
    int character = 0;                                                  // Initialize character index
    int doc_len = 0;                                                    // Initialize document length
    int last_paragraph = 0;                                             // Flag to check if the last paragraph has been reached
    
    // Loop until the last paragraph is reached
    while (!last_paragraph) {
        char*** paragraph = next_paragraph(text, &character);           // Parse the next paragraph
        last_paragraph = next_character(text, &character) == '\0';      // Check if the last character is reached

        doc_len++;
        document = realloc(document, doc_len * sizeof(char***));        // Resize the document array
        document[doc_len - 1] = paragraph;                              // Add the paragraph to the document
    }
    
    return document;
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