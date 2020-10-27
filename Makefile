TARGETS := glut_main ppm_menu
BOTH_OBJECTS := image_menu.o PPM.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o MyApp.o
GUI_OBJECTS := glut_main.o app.o gl_draw.o glut_callback.o $(BOTH_OBJECTS)
TEXT_OBJECTS := ppm_menu.o $(BOTH_OBJECTS)
CXXFLAGS := -Wall -Werror -std=c++11
LDFLAGS := -lglut -lGLU -lGL -lpthread
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
# OS X specific options
LDFLAGS := -framework OpenGL -framework GLUT -lpthread
CXXFLAGS := $(CXXFLAGS) -Wno-deprecated
endif

all: $(TARGETS)

glut_main: $(GUI_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ppm_menu: $(TEXT_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

######################################
# automatic dependency generation
#
DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))
#
#
######################################

######################################
#
#
clean:
	-rm -f $(TARGETS)
	-rm -f *.o
	-rm -f *~ .*~
	-rm -rf $(DEPDIR)
#
#
######################################

test.mp4:
	ffmpeg -r 3 -i gui_image_%04d.ppm $@

# Local Variables:
# mode:makefile
# End:

