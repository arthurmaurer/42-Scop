#ifndef OBJ_TOKENS_H
# define OBJ_TOKENS_H

# define COMMENT_TOKEN "#"
# define POSITION_TOKEN "v"
# define COLOR_TOKEN "vt"
# define NORMAL_TOKEN "vn"
# define POLYGON_TOKEN "f"

int			token_to_int(const char **tokens, int index);
int			tokens_are_enough(const char **tokens, int qty);

#endif
