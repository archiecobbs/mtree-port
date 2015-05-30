#
# Copyright 2010 Archie L. Cobbs.
# 
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.
# 

Name:           mtree
Version:        1.0.1
Release:        1
License:        BSD
Summary:        Tool for creating and verifying file hierarchies
Group:          System/Utilities
Source:         %{name}-%{version}.tar.gz
URL:            http://www.freebsd.org./
BuildRoot:      %{_tmppath}/%{name}-%{version}-root
BuildRequires:  libopenssl-devel
BuildRequires:  make
BuildRequires:  gcc

%description
The %{name} utility compares the file hierarchy rooted in the current
directory against a specification read from the standard input. Messages
are written to the standard output for any files whose characteristics do
not match the specifications, or which are missing from either the file
hierarchy or the specification.

%prep
%setup -q

%build
%{configure}
make

%install
rm -rf ${RPM_BUILD_ROOT}
%{makeinstall}

%files
%attr(0755,root,root) %{_bindir}/%{name}
%attr(0644,root,root) %{_mandir}/man5/%{name}.5.gz
%attr(0644,root,root) %{_mandir}/man8/%{name}.8.gz
%defattr(0644,root,root,0755)
%doc %{_datadir}/doc/packages/%{name}

%changelog
