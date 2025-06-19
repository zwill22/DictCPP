import os
import sys
import textwrap

sys.path.insert(0, os.path.abspath(".."))

project = 'DictCPP'
copyright = '2025, Z M Williams'
author = 'Z M Williams'
release = '0.1.0'

extensions = [
    "breathe",
    "exhale",
    "sphinx_rtd_theme",
    "myst_parser"
]

breathe_projects = {"DictCPP": "_doxygen/xml/"}
breathe_default_project = "DictCPP"

exhale_args = {
    "containmentFolder": "./_api",
    "rootFileName": "library_root.rst",
    "doxygenStripFromPath": "..",
    "rootFileTitle": "CPPDictionary",
    "createTreeView": True,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin": textwrap.dedent("""
        INPUT = ..
        FILE_PATTERNS = *.hpp *.h
        EXCLUDE_PATTERNS = */docs/* \
                           */tests/*
    """)
}

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store', ".venv"]

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

html_context = {
    "display_github": True,
    "github_user": "zwill22",
    "github_repo": "DictCPP",
    "github_version": "main",
    "conf_py_path": "/docs/",
}
