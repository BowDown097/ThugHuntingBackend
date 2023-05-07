#include "qttubeannotations.h"
#include "thuggallery.h"
#define SERVER_URL "http://localhost:9990"

void fn(struct mg_connection* c, int ev, void* ev_data, void* fn_data)
{
    if (ev != MG_EV_HTTP_MSG)
        return;

    struct mg_http_message* hm = (struct mg_http_message*)ev_data;
    if (mg_http_match_uri(hm, "/qttube_annotations"))
        qttube_annotations_fn(c, hm);
    else if (mg_http_match_uri(hm, "/thuggallery/api/random"))
        thuggallery_random_fn(c, hm);
    else
        mg_http_reply(c, 404, NULL, "Nothing at this endpoint");
}

int main(void)
{
    srand(time(NULL));
    mg_log_set(MG_LL_ERROR);
    printf("Launching on %s\n", SERVER_URL);

    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, SERVER_URL, fn, &mgr);
    while (true) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}
