Level* create_level(char* level_file);
void update_level(Game* game, Level* level, int infinite);
void free_level(Level* level);
void create_object_line(Game *game, char* object_line);
EntityType get_object_type(char object);