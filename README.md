# Description

  Reproduces a `::CORBA::MARSHAL` throw when demarshalling a valuetype
  derived from another one that supports an abstract interface.

# Dependencies

  ACE+TAO. Specifically, the following libraries: ACE, TAO,
  TAO_AnyTypeCode, TAO_PortableServer, TAO_Valuetype.

# Usage

  - Load the build environment variables present in `ace_tao.env`.
    Before this, make sure to set the `$ROOT` environment variable
    inside the script properly.

        $ . ace_tao.env

  - Build the demo.

        $ make

    If necessary, debug symbols can be added to the objects.

        $ make CXXFLAGS=-g

  - To run the demo for the first time, you need to load the server and
    then the client.

        $ ./server
        ...
        $ ./client file://cpp_test_server.ior

    This first run will fail, as the client throws a `::CORBA::MARSHAL`
    exception.

  - There is a known workaround for the failure in the first run. It is
    in the interface definition source file. To apply this workaround,
    rebuild the demo with the following commands:

        $ make mrproper # it will remove all build artifacts
        $ make IDLFLAGS=-DWORKAROUND

    Or either:

        $ make -B IDLFLAGS=-DWORKAROUND

  - A new execution of the demo should not present the problem.

# Author

  Tadeu Bastos <<tadeu1@gmail.com>>

<!-- vim::tw=72 et ai
-->
