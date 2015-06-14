#include <iostream>

#include "testS.h"
#include "impl.h"

namespace test
{
    AnAbstractInterface *Producer_impl::produce()
    {
        ADerivedValueType_var dvt(new ADerivedValueType_impl);
        dvt->content("(C++) I am the only one.");
        return dvt._retn();
    }

    AnAbstractInterfaceSeq *Producer_impl::produceSequence()
    {
        ADerivedValueType_var dvt[2] = {
            new ADerivedValueType_impl,
            new ADerivedValueType_impl
        };
        dvt[0]->content("(C++) I am the first.");
        dvt[1]->content("(C++) I am the second.");

        AnAbstractInterfaceSeq_var dvts(new AnAbstractInterfaceSeq);
        dvts->length(2);
        dvts[0] = dvt[0]._retn();
        dvts[1] = dvt[1]._retn();
        return dvts._retn();
    }
};
