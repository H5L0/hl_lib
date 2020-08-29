



int hl_file_move(int fd, const char *path, bool copy);

int hl_file_rename(int fd, const char *name);

int hl_file_delete(int fd);




int hl_fs_move(const char *path_source, const char *path_target);

//delete / rename
//int hl_fs_modify(const char *path, int operation);

int hl_fs_rename(const char *path, const char *name);

int hl_fs_delete(const char *path);


int hl_fs_exists(const char *path);


//int hl_fs_create_dir();

int hl_directory_create();

int hl_directory_rename();


int hl_fs_delete();



