#include <iostream>
#include <cassert>
#include "testC.h"

void callProduce(test::Producer_ptr producer);
void callProduceSequence(test::Producer_ptr producer);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "error: no IOR file specified" << std::endl;
        std::exit(1);
    }
    std::string ior_file(argv[1]);
    CORBA::ORB_var orb(CORBA::ORB_init(argc, argv));
    test::ADerivedValueType_init *dvt_factory(new test::ADerivedValueType_init);
    orb->register_value_factory(dvt_factory->tao_repository_id(), dvt_factory);
    dvt_factory->_remove_ref();
    CORBA::Object_var obj(orb->string_to_object(ior_file.c_str()));
    assert(!CORBA::is_nil(obj.in()));
    test::Producer_var producer(test::Producer::_narrow(obj.in()));
    callProduce(producer.in());
    callProduceSequence(producer.in());
    orb->destroy();
}

void callProduce(test::Producer *producer)
{
    test::AnAbstractInterface_var ai(producer->produce());
    test::ADerivedValueType_var dvt(test::ADerivedValueType::_downcast(
        ai->_to_value()));
    std::cout << dvt->content() << std::endl << std::flush;
}

void callProduceSequence(test::Producer *producer)
{
    test::AnAbstractInterfaceSeq_var ais(producer->produceSequence());
    test::ADerivedValueType_var dvts[2] = {
        test::ADerivedValueType::_downcast(ais[0]->_to_value()),
        test::ADerivedValueType::_downcast(ais[1]->_to_value())
    };
    std::cout << dvts[0]->content() << std::endl;
    std::cout << dvts[1]->content() << std::endl;
}
