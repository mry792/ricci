#! /usr/bin/env python3

from pathlib import Path

from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import update_conandata
from conan.tools.scm import Git


class RicciRecipe (ConanFile):
    name = 'ricci'
    # version = (computed from local repo)

    author = 'M. Emery Goss <m.goss792@gmail.com>'
    url = 'https://github.com/mry792/ricci.git'
    description = 'Library for compile-time tensor calculus.'

    settings = 'os', 'compiler', 'build_type', 'arch',

    def _has_git_repo (self, path):
        try:
            resolved_path = Path(path).resolve()
            git = Git(self, resolved_path)
            repo_root = Path(git.get_repo_root()).resolve()
            return resolved_path == repo_root
        except Exception:
            return False

    def set_version (self):
        if not self.version:
            git = Git(self, self.recipe_folder)
            tag = git.run('describe --tags --match v*.*.*')
            self.version = tag[1:]

    ###
    # RECIPE STEPS
    ###

    def export (self):
        if self._has_git_repo(self.recipe_folder):
            git = Git(self, self.recipe_folder)
            scm_url, scm_commit = git.get_url_and_commit()
            update_conandata(self, {
                'source': {
                    'commit': scm_commit,
                    'url': scm_url,
                }
            })
            return

        update_conandata(self, {
            'source': { 'url': '(local)' }
        })

    def export_sources (self):
        if not self._has_git_repo(self.recipe_folder):
            def copy_src (pattern):
                copy(self, pattern, self.recipe_folder, self.export_sources_folder)

            copy_src('*.hpp')
            copy_src('*.cpp')
            copy_src('CMakeLists.txt')
            copy_src('LICENSE')
            copy_src('README.md')

    def layout (self):
        cmake_layout(self)

    tool_requires = 'brokkr/0.2.5@egoss/stable'

    def package_id (self):
        # header-only library
        self.info.clear()

    def validate (self):
        if self.settings.get_safe('compiler.cppstd'):
            check_min_cppstd(self, 20)

    def source (self):
        source = self.conan_data['source']
        if source['url'] != '(local)':
            self._git.clone(source['url'], target = '.')
            self._git.checkout(source['commit'])

    def generate (self):
        CMakeDeps(self).generate()

        tc = CMakeToolchain(self)
        if self.conan_data and self.conan_data['source']['url'] == '(local)':
            tc.cache_variables['BROKKR_THIS_PROJECT_VERSION:STRING'] = self.version
        tc.generate()

    def build (self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package (self):
        cmake = CMake(self)
        cmake.install()

    def package_info (self):
        self.cpp_info.set_property('cmake_find_mode', 'none')
