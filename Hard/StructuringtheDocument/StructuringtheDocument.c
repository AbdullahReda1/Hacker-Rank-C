#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
#define DEFAULT_LEN    8

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int    word_count;             //denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data;
    int    sentence_count;         //denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int    paragraph_count;        //denotes number of paragraphs in a document
};

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
/// @return word struct - the word
struct word next_word(char* text, int* character) {
    char* word = malloc(DEFAULT_LEN * sizeof(char));    // Allocate initial memory for the word
    int word_size = 0;                                  // Initialize word size

    // Loop through characters until a non-text character is encountered
    while (is_text(text[*character])) {
        char ch = next_character(text, character);      // Get the next character
        insert_char(&word, &word_size, ch);             // Insert the character into the word
    }
    
    insert_char(&word, &word_size, '\0');               // Null-terminate the word

    // Move word array to the data array of the word structure
    struct word W;
    W.data = word;

    return W;
}

/// @brief Function to parse the next sentence from the text
/// @param text pointer to char
/// @param character pointer to int
/// @return sentence struct - the sentence
struct sentence next_sentence(char* text, int* character) {
    struct sentence S;
    S.data = malloc(DEFAULT_LEN * sizeof(struct word));                     // Allocate initial memory for the sentence
    S.word_count = 0;                                                       // Initialize sentence length
    
    // Loop through characters until a sentence terminator is encountered
    while (!is_sentence_terminator(text[*character])) {
        trim_whitespace(text, character);                                   // Trim leading whitespace
        struct word W = next_word(text, character);                         // Parse the next word

        S.word_count++;
        S.data = realloc(S.data, S.word_count * sizeof(struct word));       // Resize the sentence array
        S.data[S.word_count - 1] = W;                                       // Add the word to the sentence
    }
    
    next_character(text, character);                                        // Move past the period
    return S;
}

/// @brief Function to parse the next paragraph from the text
/// @param text pointer to char
/// @param character pointer to int
/// @return paragraph struct - the paragraph
struct paragraph next_paragraph(char* text, int* character) {
    struct paragraph P;
    P.data = malloc(DEFAULT_LEN * sizeof(struct sentence));                     // Allocate initial memory for the paragraph
    P.sentence_count = 0;                                                       // Initialize paragraph length
    
    // Loop through characters until a paragraph terminator is encountered
    while (!is_paragraph_terminator(text[*character])) {
        struct sentence S = next_sentence(text, character);                     // Parse the next sentence

        P.sentence_count++;
        P.data = realloc(P.data, P.sentence_count * sizeof(struct sentence));   // Resize the paragraph array
        P.data[P.sentence_count - 1] = S;                                       // Add the sentence to the paragraph
    }
    
    return P;
}

/// @brief Function to parse the entire document from the text
/// @param text pointer to char
/// @return document struct - the document
struct document get_document(char* text) {
    struct document D;
    D.data = malloc(DEFAULT_LEN * sizeof(struct paragraph));                    // Allocate initial memory for the document
    D.paragraph_count = 0;                                                      // Initialize document length
    int character = 0;                                                          // Initialize character index
    int last_paragraph = 0;                                                     // Flag to check if the last paragraph has been reached
    
    // Loop until the last paragraph is reached
    while (!last_paragraph) {
        struct paragraph P = next_paragraph(text, &character);                  // Parse the next paragraph
        last_paragraph = next_character(text, &character) == '\0';              // Check if the last character is reached

        D.paragraph_count++;
        D.data = realloc(D.data, D.paragraph_count * sizeof(struct paragraph)); // Resize the document array
        D.data[D.paragraph_count - 1] = P;                                      // Add the paragraph to the document
    }
    
    return D;
}

/// @brief Return the k-th word in the m-th sentence of the n-th paragraph
/// @param document the document
/// @param k the words
/// @param m the sentences
/// @param n the paragraphs
/// @return word struct
struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n - 1].data[m - 1].data[k - 1];
}

/// @brief Return the k-th sentence in the m-th paragraph
/// @param document the document
/// @param k the sentences
/// @param m the paragraphs
/// @return sentence struct
struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m - 1].data[k - 1];
}

/// @brief Return the k-th paragraph
/// @param document the document
/// @param k the paragraphs
/// @return paragraph struct
struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k - 1];
}

void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
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

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}