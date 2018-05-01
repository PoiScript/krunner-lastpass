#ifndef LPASS_H
#define LPASS_H

#include <KRunner/AbstractRunner>

class Runner : public Plasma::AbstractRunner {

Q_OBJECT

public:
    Runner(QObject *parent, const QVariantList &args);

    void match(Plasma::RunnerContext &) override;

    void run(const Plasma::RunnerContext &, const Plasma::QueryMatch &) override;
};

K_EXPORT_PLASMA_RUNNER(lpass, Runner)

#endif
