#include "main.h"

#include <KLocalizedString>
#include <QApplication>
#include <QClipboard>

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

    QList<Plasma::QueryMatch> matches;
    Plasma::QueryMatch match(this);
    match.setType(Plasma::QueryMatch::InformationalMatch);
    match.setIcon(QIcon::fromTheme("lock"));
    match.setText(QLatin1String("Hello World from krunner-lpass"));
    matches.append(match);
    context.addMatches(matches);
}

void Runner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) {
    Q_UNUSED(context);
    QApplication::clipboard()->setText(match.text());
}

// Meta object code
#include "moc_main.cpp"
