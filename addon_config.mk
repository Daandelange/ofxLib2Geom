meta:
	ADDON_NAME = ofxBezierRs
	ADDON_DESCRIPTION = OF wrapper for lib2geom, providing a set geometrical functions on vector data.
	ADDON_AUTHOR = Daan de Lange
	ADDON_TAGS = "Geometry" "Algorithms" "Animation"
	ADDON_URL = https://github.com/daandelange/ofxLib2Geom

common:
    #ADDON_SOURCES_EXCLUDE = libs/lib2geom/%
    ADDON_SOURCES_EXCLUDE = libs/lib2geom/tests/%
    ADDON_SOURCES_EXCLUDE += libs/lib2geom/src/%
    ADDON_SOURCES_EXCLUDE += libs/lib2geom/build/%
	#ADDON_INCLUDES_EXCLUDE = libs/lib2geom/%
    #ADDON_EXCLUDES = libs/lib2geom/*
	ADDON_INCLUDES = src/
	ADDON_INCLUDES += libs/lib2geom/include/
    #ADDON_SOURCES += libs/lib2geom/src/%
    #ADDON_CPPFLAGS = -std=c++17

osx:


linux64:
    ADDON_LDFLAGS = -l2geom -lgsl -ldouble-conversion
    #ADDON_INCLUDES = 
    #ADDON_LIBS = libs/2geom/lib/linux64/lib2geom.a

linuxarmv7l:


vs:


