#include <fstream>
#include "testS.h"
#include "impl.h"

int
main(int argc, char *argv[])
{
    CORBA::ORB_var orb(CORBA::ORB_init(argc, argv));
    test::ADerivedValueType_init *dvt_factory(new test::ADerivedValueType_init);
    orb->register_value_factory(dvt_factory->tao_repository_id(), dvt_factory);
    dvt_factory->_remove_ref();
    CORBA::Object_var poa_object(orb->resolve_initial_references("RootPOA"));
    PortableServer::POA_var root_poa(PortableServer::POA::_narrow(
        poa_object.in()));
    PortableServer::POAManager_var poa_manager(root_poa->the_POAManager());
    poa_manager->activate();
    test::Producer_impl servant;
    PortableServer::ObjectId_var id(root_poa->activate_object(&servant));
    CORBA::Object_var object(root_poa->id_to_reference(id.in()));
    test::Producer_var server(test::Producer::_narrow(object.in()));
    CORBA::String_var ior(orb->object_to_string(server.in()));
    std::ofstream out("cpp_test_server.ior", std::ofstream::trunc);
    out << ior;
    out.close();
    orb->run();
    root_poa->destroy(1, 1);
    orb->destroy();
}
