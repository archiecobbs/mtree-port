pkgname		:= mtree
specname	?= $(pkgname).spec
pwd		:= $(shell pwd)
NAME		?= $(shell rpmspec -q --qf "%{name}\n" $(specname)|head -1)
VERSION		?= $(shell rpmspec -q --qf "%{version}\n" $(specname)|head -1)
RELEASE		?= $(shell rpmspec -q --qf "%{release}\n" $(specname)|head -1)
NVR		:= $(NAME)-$(VERSION)-$(RELEASE)
source		:= $(NAME)-$(VERSION).tar.gz

default: srpm

all: rpm srpm

name:
	@echo $(NVR)

rpm:
	rpmbuild \
                --define '_sourcedir $(pwd)' \
                --define '_specdir $(pwd)' \
                --define '_builddir $(pwd)' \
                --define '_srcrpmdir $(pwd)' \
                --define '_rpmdir $(pwd)' \
                -bb ./$(specname)

srpm: $(NVR).src.rpm

$(NVR).src.rpm: $(specname) $(source) $(wildcard *.diff)
	rpmbuild \
                --define '_sourcedir $(pwd)' \
                --define '_specdir $(pwd)' \
                --define '_builddir $(pwd)' \
                --define '_srcrpmdir $(pwd)' \
                --define '_rpmdir $(pwd)' \
                --nodeps \
                -bs ./$(specname)


$(NAME)-$(VERSION).tar.gz: $(shell git ls-files)
	git archive --format=tar.gz -o $@ --prefix=$(NAME)-$(VERSION)/ HEAD ./

builddep: $(NVR).src.rpm
ifeq ($(shell grep '^NAME=' /etc/os-release),NAME=Fedora)
	dnf builddep -y $<
endif

rebuild: builddep
	rpmbuild --rebuild $(NVR).src.rpm

clean:
	rm -rf *~ *.rpm noarch

