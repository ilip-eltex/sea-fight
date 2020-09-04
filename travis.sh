#!/bin/bash
if [ "$TRAVIS_BRANCH" = "dev" ]; then 
	make
	exit $?
fi
if [ "$TRAVIS_BRANCH" = "master" ]; then
	make
    #./sea-fight
fi
if [ "$TRAVIS_BRANCH" = "test"]; then
    make test
fi