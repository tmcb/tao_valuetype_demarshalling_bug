namespace test
{
    class ADerivedValueType_impl
    : public virtual ::OBV_test::ADerivedValueType
    , public virtual ::CORBA::DefaultValueRefCountBase
    {
    };

    class Producer_impl
    : public virtual ::POA_test::Producer
    {
    public:
        AnAbstractInterface    *produce();
        AnAbstractInterfaceSeq *produceSequence();
    };
};
