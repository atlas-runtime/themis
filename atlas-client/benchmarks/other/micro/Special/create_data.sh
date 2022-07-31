#!/bin/bash
dd if=/dev/urandom bs=20000000 count=1 | base64 > ./data