project = 'sha-3'
copyright = '2025, gdaneek'
author = 'gdaneek'
release = '1.3.3'

extensions = ['breathe', 'exhale', 'sphinx_rtd_theme']
breathe_projects = {
    "My C++ Project": "../../build/xml"
}
breathe_default_project = "My C++ Project"

templates_path = ['_templates']
exclude_patterns = []

exhale_args = {
    "containmentFolder": "api",
    "rootFileName": "library_root.rst",
    "rootFileTitle": "API Reference",
    "doxygenStripFromPath": "..",
    "createTreeView": True,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin": "INPUT = ../../include"
}

html_theme = 'sphinx_rtd_theme'
