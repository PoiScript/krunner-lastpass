#ifndef LASTPASS_H
#define LASTPASS_H

// used in c
struct MatchedAccount {
    char *name;
    char *password;
};

#ifdef __cplusplus
// used in c++
struct ShowedAccount {
    QString name;
    QString password;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern int search(char *);
extern void match(struct MatchedAccount *);

#ifdef __cplusplus
}
#endif

#endif /*LASTPASS_H*/