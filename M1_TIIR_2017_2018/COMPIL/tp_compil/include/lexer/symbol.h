#ifndef SYMBOL_H
#define SYMBOL_H

/* tokens based on typographical marks and signs */
#define SIGNS                0
#define COLON                (SIGNS|1)
#define COMMA                (SIGNS|2)
#define SEMICOLON            (SIGNS|3)
#define FULL_STOP            (SIGNS|4)
#define PLUS                 (SIGNS|5)
#define MINUS                (SIGNS|6)
#define ASTERISK             (SIGNS|7)
#define CLOSE_COMMENT        (SIGNS|8)
#define SLASH                (SIGNS|9)
#define OPEN_COMMENT         (SIGNS|10)
#define BACKSLASH            (SIGNS|11)
#define OPEN_PARENTHESIS     (SIGNS|12)
#define CLOSE_PARENTHESIS    (SIGNS|13)
#define OPEN_BRACKET         (SIGNS|14)
#define CLOSE_BRACKET        (SIGNS|15)
#define OPEN_BRACE           (SIGNS|16)
#define CLOSE_BRACE          (SIGNS|17)
#define ASSIGNMENT           (SIGNS|18)
#define EQUAL                (SIGNS|19)
#define LESS_THAN            (SIGNS|20)
#define LESS_OR_EQUAL        (SIGNS|21)
#define GREATER_THAN         (SIGNS|22)
#define GREATER_OR_EQUAL     (SIGNS|23)
#define AMPERSAND            (SIGNS|24)
#define PIPE                 (SIGNS|25)
#define CARET                (SIGNS|26)
#define EXCLAMATION_MARK     (SIGNS|27)
#define NOT_EQUAL            (SIGNS|28)
#define QUESTION_MARK        (SIGNS|29)
#define QUOTE                (SIGNS|30)
#define DOUBLE_QUOTE         (SIGNS|31)
#define AT                   (SIGNS|32)
#define HASH                 (SIGNS|33)
#define PERCENT              (SIGNS|34)
#define TILDE                (SIGNS|35)
#define SECTION_MARK         (SIGNS|36)
#define INCREMENT            (SIGNS|37)
#define DECREMENT            (SIGNS|38)
#define EXPONENTIATION       (SIGNS|39)
#define SHIFT_LEFT           (SIGNS|40)
#define SHIFT_RIGHT          (SIGNS|41)
#define SHIFT_RIGHT_UNSIGNED (SIGNS|42)
#define STRICT_EQUAL         (SIGNS|43)
#define STRICT_NOT_EQUAL     (SIGNS|44)
#define LOGICAL_AND          (SIGNS|45)
#define LOGICAL_XOR          (SIGNS|46)
#define LOGICAL_OR           (SIGNS|47)
#define PLUS_ASSIGNMENT      (SIGNS|48)
#define MINUS_ASSIGNMENT     (SIGNS|49)
#define MUL_ASSIGNMENT       (SIGNS|50)
#define DIV_ASSIGNMENT       (SIGNS|51)
#define MOD_ASSIGNMENT       (SIGNS|52)
#define SHIFT_LEFT_ASSIGNMENT (SIGNS|53)
#define SHIFT_RIGHT_ASSIGNMENT (SIGNS|54)
#define SHIFT_RIGHT_UNSIGNED_ASSIGNMENT (SIGNS|55)
#define AND_ASSIGNMENT       (SIGNS|56)
#define XOR_ASSIGNMENT       (SIGNS|57)
#define OR_ASSIGNMENT        (SIGNS|58)
#define NOT_ASSIGNMENT       (SIGNS|59)
#define NB_SIGNS             59

/* tokens based on keywords */
#define KEYWORDS             64
#define FUNCTION             (KEYWORD|1)
#define RETURN               (KEYWORD|2)
#define VAR                  (KEYWORD|3)
#define IF                   (KEYWORD|4)
#define ELSE                 (KEYWORD|5)
#define WHILE                (KEYWORD|6)
#define FOR                  (KEYWORD|7)
#define BREAK                (KEYWORD|8)
#define CASE                 (KEYWORD|9)
#define CATCH                (KEYWORD|10)
#define CONTINUE             (KEYWORD|11)
#define DEBUGGER             (KEYWORD|12)
#define DEFAULT              (KEYWORD|13)
#define DELETE               (KEYWORD|14)
#define DO                   (KEYWORD|15)
#define FALSE                (KEYWORD|16)
#define FINALLY              (KEYWORD|17)
#define IN                   (KEYWORD|18)
#define INSTANCEOF           (KEYWORD|19)
#define NEW                  (KEYWORD|20)
#define NULL_TOKEN           (KEYWORD|21)
#define SWITCH               (KEYWORD|22)
#define THIS                 (KEYWORD|23)
#define THROW                (KEYWORD|24)
#define TRUE                 (KEYWORD|25)
#define TRY                  (KEYWORD|26)
#define TYPEOF               (KEYWORD|27)
#define VOID                 (KEYWORD|28)
#define WITH                 (KEYWORD|29)
#define NB_KEYWORDS          29

/* valued tokens */
#define VALUED               128
#define IDENTIFIER           (VALUED|1)
#define INTEGER              (VALUED|2)
#define FLOAT                (VALUED|3)
#define STRING               (VALUED|4)
#define CHAR                 (VALUED|5)


static char *signs[NB_SIGNS] = {
        /* COLUMN            */     ":",
        /* COMMA             */     ",",
        /* SEMICOLUMN        */     ";",
        /* FULLSTOP          */     "",
        /* PLUS              */     "+",
        /* MINUS             */     "-",
        /* ASTERISK          */     "*",
        /* CLOSE_COMMENT     */     "",
        /* SLASH             */     "/",
        /* OPEN_COMMENT      */     "",
        /* BACKSLASH         */     "",
        /* OPEN_PARENTHESIS  */     "(",
        /* CLOSE_PARENTHESIS */     ")",
        /* OPEN_BRACKET      */     "[",
        /* CLOSE_BRACKET     */     "]",
        /* OPEN_BRACE        */     "{",
        /* CLOSE_BRACE       */     "}",
        /* ASSIGNMENT        */     "=",
        /* EQUAL             */     "==",
        /* LESS_THAN         */     "<",
        /* LESS_OR_EQUAL     */     "<=",
        /* GREATER_THAN      */      ">",
        /* GREATER_OR_EQUAL  */     ">=",
        /* AMPERSAND         */      "&",
        /* PIPE              */      "|",
        /* CARET             */      "^",
        /* EXCLAMATION_MARK */       "!",
        /* NOT_EQUAL */             "!=",
        /* QUESTION_MARK     */      "?",
        /* QUOTE             */       "'",
        /* DOUBLE_QUOTE      */       "\"",
        /* AT                */       "@",
        /* HASH              */       "#",
        /* PERCENT           */      "%",
        /* TILDE             */      "~",
        /* SECTION_MARK      */       "",
        /* INCREMENT */             "++",
        /* DECREMENT */             "--",
        /* EXPONENTIATION */        "**",
        /* SHIFT_LEFT */            "<<",
        /* SHIFT_RIGHT */           ">>",
        /* SHIFT_RIGHT_UNSIGNED */ ">>>",
        /* STRICT_EQUAL     */     "===",
        /* STRICT_NOT_EQUAL */     "!==",
        /* LOGICAL_AND */           "&&",
        /* LOGICAL_XOR  */          "^^",
        /* LOGICAL_OR */            "||",
        /* PLUS_ASSIGNMENT */    "+=",
        /* MINUS_ASSIGNMENT */   "-=",
        /* MUL_ASSIGNMENT */      "*=",
        /* DIV_ASSIGNMENT */     "/=",
        /* MOD_ASSIGNMENT */     "%=",
        /* SHIFT_LEFT_ASSIGNMENT */  "<<=",
        /* SHIFT_RIGHT_ASSIGNMENT */ ">>=",
        /* SHIFT_RIGHT_UNSIGNED_ASSIGNMENT */ ">>>=",
        /*  AND_ASSIGNMENT */      "&=",
        /*  XOR_ASSIGNMENT  */     "^=",
        /*  OR_ASSIGNMENT */       "|=",
        /*  NOT_ASSIGNMENT */      "~=",
};

static char *keywords[NB_KEYWORDS + 1] = {
        "",
        /* SECTION_MARK */      "function",
        /* SECTION_MARK */      "return",
        /* SECTION_MARK */      "var",
        /* SECTION_MARK */      "if",
        /* SECTION_MARK */      "else",
        /* SECTION_MARK */      "while",
        /* SECTION_MARK */      "for",
        /* SECTION_MARK */      "break",
        /* SECTION_MARK */      "case",
        /* SECTION_MARK */      "catch",
        /* SECTION_MARK */      "continue",
        /* SECTION_MARK */      "debugger",
        /* SECTION_MARK */      "default",
        /* SECTION_MARK */      "delete",
        /* SECTION_MARK */      "do",
        /* SECTION_MARK */      "false",
        /* SECTION_MARK */      "finally",
        /* SECTION_MARK */      "in",
        /* SECTION_MARK */      "instanceof",
        /* SECTION_MARK */      "new",
        /* SECTION_MARK */      "null_token",
        /* SECTION_MARK */      "switch",
        /* SECTION_MARK */      "this",
        /* SECTION_MARK */      "throw",
        /* SECTION_MARK */      "true",
        /* SECTION_MARK */      "try",
        /* SECTION_MARK */      "typeof",
        /* SECTION_MARK */      "void",
        /* SECTION_MARK */      "with"
};

#endif