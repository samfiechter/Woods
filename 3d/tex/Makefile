L_GNUSTD = /usr/lib/gcc/darwin/default/libstdc++.a
L_PGSQL = /usr/local/pgsql/lib/libpq.a

INCLS = 
LIBS =  $(L_GNUSTD) -lm

CFLAGS = -g -O3 -D NO_GL
#  -frepo -falt-external-templates 
#  -falt-external-templates  -findirect-virtual-calls 
# -findirect-virtual-calls -fno-implicit-templates
# -fno-access-control  -fcheck-new  -fconserve-space
#           -fno-const-strings  -fdollars-in-identifiers -fno-
#           elide-constructors -fno-enforce-eh-specs  -fexternal-
#           templates -falt-external-templates -ffor-scope  -fno-
#           for-scope  -fno-gnu-keywords 
#           -fno-implicit-inline-templates -fno-implement-inlines
#           (APPLE ONLY) -fapple-kext
#           (APPLE ONLY) -fcoalesce-templates (APPLE ONLY) -fms-
#           extensions -fno-nonansi-builtins  -fno-operator-names
#           -fno-optional-diags  -fpermissive -frepo  -fno-rtti
#           -fstats  -ftemplate-depth-n -fuse-cxa-atexit
#           -fvtable-gc  -fno-weak  -nostdinc++ -fno-default-
#           inline  -Wctor-dtor-privacy -Wnon-virtual-dtor  -Wre-
#           order -Weffc++  -Wno-deprecated -Wno-non-template-
#           friend  -Wold-style-cast -Woverloaded-virtual  -Wno-
#           pmf-conversions -Wsign-promo  -Wsynth
#
CC = g++ $(CFLAGS)

OBJS = model.o main.o obj_base.o

%.o: %.cc %.h
	date
	etags -C -a $^
	$(CC) -c $< $(INCLS)

%.o: %.cc 
	date
	etags -C -a $^
	$(CC) -c $< $(INCLS)

%.a: %.o
	date
	ar -vq $@ $^

%: %.o
	date
	$(CC) $^ $(LIBS) -o $@  


tex : treeexda.o treetexdta.o

clean:
	rm -f *.o
	rm -f *.so
	rm -f *.rpo
	rm -f TAGS












