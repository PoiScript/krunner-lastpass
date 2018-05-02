#include "lastpass-cli/cmd.h"
#include "lastpass-cli/cipher.h"
#include "lastpass-cli/util.h"
#include "lastpass-cli/config.h"
#include "lastpass-cli/agent.h"
#include "lastpass-cli/kdf.h"
#include "lastpass-cli/endpoints.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "lastpass.h"

int search(char *text) {
    unsigned char key[KDF_HASH_LEN];
    struct session *session = NULL;
    struct field;
    struct account *found, *account;
    enum blobsync sync = BLOB_SYNC_NO;
    struct list_head matches, potential_set;
    int fields = ACCOUNT_NAME | ACCOUNT_ID | ACCOUNT_FULLNAME;
    struct blob *blob = NULL;

    init_all(sync, key, &session, &blob);

    INIT_LIST_HEAD(&matches);
    INIT_LIST_HEAD(&potential_set);

    list_for_each_entry(account, &blob->account_head, list)
        list_add(&account->match_list, &potential_set);

    find_matching_regex(&potential_set, text, fields, &matches);

    if (list_empty(&matches))
        return 1;

    found = list_first_entry(&matches, struct account, match_list);

    list_for_each_entry(account, &matches, match_list) {
        found = account;
        lastpass_log_access(sync, session, key, found);

        if (strlen(found->password)) {
            struct MatchedAccount account_;
            account_.name = found->name;
            account_.password = found->password;
            match(&account_);
        }
    }

    session_free(session);
    blob_free(blob);
    return 0;
}
