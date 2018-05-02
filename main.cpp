#include "main.h"
#include "lastpass.h"

#include <QApplication>
#include <QClipboard>

QList<ShowedAccount> accounts;

void match(MatchedAccount *fred) {
    ShowedAccount account;
    account.name = fred->name;
    account.password = fred->password;
    accounts.append(account);
}

Runner::Runner(QObject *parent, const QVariantList &args) : Plasma::AbstractRunner(parent, args) {
    Q_UNUSED(args);

    setObjectName(QLatin1String("LastPass"));
    setHasRunOptions(true);
    setIgnoredTypes(Plasma::RunnerContext::Directory |
                    Plasma::RunnerContext::File |
                    Plasma::RunnerContext::NetworkLocation);
    setPriority(HighestPriority);
}

void Runner::match(Plasma::RunnerContext &context) {
    QString text = context.query();

    if (!context.isValid())
        return;

    if (search(text.toLatin1().data()) != 0)
        return;

    QList<Plasma::QueryMatch> matches;
    Q_FOREACH(ShowedAccount account, accounts) {
        Plasma::QueryMatch match(this);
        match.setType(Plasma::QueryMatch::InformationalMatch);
        match.setIcon(QIcon::fromTheme("lock"));
        match.setText(account.name);
        match.setData(account.password);
        matches.append(match);
    }
    context.addMatches(matches);

    accounts.clear();
}

void Runner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) {
    Q_UNUSED(context);

    // FIXME: the password will show up in the input instead of copying to clipboard
    QString password = match.data().toString();
    QApplication::clipboard()->setText(password);
}

// Meta object code
#include "moc_main.cpp"
