#include "thuggallery.h"
#define THUG_PATH "/usr/share/nginx/thughuntingparty/thuggallery/thug"

int num_entries(const char* path)
{
    int ret = 0;

    DIR* d;
    if ((d = opendir(path)) == NULL)
        return -1;

    char* buf = malloc(strlen(path) + 1024);
    struct dirent* ds;
    while ((ds = readdir(d)) != NULL)
    {
        if (strcmp(ds->d_name, ".") == 0 || strstr(ds->d_name, "./") != NULL)
            continue;

        snprintf(buf, sizeof(buf), "%s/%s", path, ds->d_name);

        struct stat st;
        stat(buf, &st);

        if (S_ISREG(st.st_mode) || S_ISDIR(st.st_mode))
            ++ret;
    }

    free(buf);
    closedir(d);
    return ret;
}

void thuggallery_random_fn(struct mg_connection* c, struct mg_http_message* hm)
{
    int file_count = num_entries(THUG_PATH);
    if (file_count <= 0)
    {
        mg_http_reply(c, 500, NULL, "Could not open thug directory or thug directory is empty");
        return;
    }

    int r_file_index = rand() % file_count;

    DIR* d;
    if ((d = opendir(THUG_PATH)) == NULL)
    {
        mg_http_reply(c, 500, NULL, "Could not open thug directory");
        return;
    }

    char* buf = malloc(strlen(THUG_PATH) + 1024);
    struct dirent* ds;
    int i = 0;

    while ((ds = readdir(d)) != NULL)
    {
        if (strcmp(ds->d_name, ".") == 0 || strstr(ds->d_name, "./") != NULL)
            continue;

        snprintf(buf, sizeof(buf), "%s/%s", THUG_PATH, ds->d_name);

        struct stat st;
        stat(buf, &st);

        if (S_ISREG(st.st_mode) || S_ISDIR(st.st_mode))
        {
            ++i;
            if (i == r_file_index)
            {
                struct mg_http_serve_opts opts = {};
                mg_http_serve_file(c, hm, buf, &opts);
            }
        }
    }

    free(buf);
    closedir(d);
}
