#ifndef RULES_H
#define RULES_H

extern char *signs[34];
extern char *keywords[29];

struct tree_s* terme();
struct tree_s* facteur();
struct tree_s* expression();

#endif
