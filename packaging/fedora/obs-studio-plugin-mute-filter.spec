Name: obs-studio-plugin-mute-filter
Version: @VERSION@
Release: @RELEASE@%{?dist}
Summary: Discard audio plugin for OBS Studio
License: GPLv2+

Source0: %{name}-%{version}.tar.bz2
BuildRequires: cmake, gcc, gcc-c++
BuildRequires: obs-studio-devel

%description
A plugin for OBS Studio to discard audio for a source.

%prep
%autosetup -p1

%build
%{cmake} -DINSTALL_LICENSE_FILES:BOOL=OFF
%{cmake_build}

%install
%{cmake_install}

%files
%{_libdir}/obs-plugins/*.so
%{_datadir}/obs/obs-plugins/*/
%license LICENSE
