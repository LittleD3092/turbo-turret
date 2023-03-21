from setuptools import find_packages
from setuptools import setup

setup(
    name='controller_input_srv',
    version='0.0.0',
    packages=find_packages(
        include=('controller_input_srv', 'controller_input_srv.*')),
)
