override CXXFLAGS:=-I$(ACE_ROOT) -I$(TAO_ROOT) $(CXXFLAGS)
override LDFLAGS:=-L$(ACE_ROOT)/lib -lACE -lTAO -lTAO_AnyTypeCode -lTAO_PortableServer -lTAO_Valuetype $(LDFLAGS)
override IDLFLAGS:=$(IDLFLAGS)

all: client server

stubs:=%C.inl %C.h %C.cpp
.PRECIOUS: $(stubs)
$(stubs): %.idl
	$(ACE_ROOT)/bin/tao_idl $(IDLFLAGS) -SS -Ssh $<

skeletons:=%S.h %S.cpp
.PRECIOUS: $(skeletons)
$(skeletons): %.idl
	$(ACE_ROOT)/bin/tao_idl $(IDLFLAGS) -Scc -Sch -Sci $<

testC.o: testC.inl testC.h

testS.o: testC.inl testC.h testS.h

impl.o: impl.h testS.o

client: testC.o

server: impl.o testC.o testS.o

.PHONY: clean
clean:
	rm -f *.o client server

.PHONY: clean-stubs
clean-stubs:
	rm -f *C.inl *C.h *C.cpp

.PHONY: clean-skeletons
clean-skeletons:
	rm -f *S.h *S.cpp

.PHONY: clean-ior
clean-ior:
	rm -f ior

.PHONY: mrproper
mrproper: clean clean-stubs clean-skeletons clean-ior
