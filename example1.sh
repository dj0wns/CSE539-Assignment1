#!/bin/bash

bin/crypto c 12345678 examples/example1 examples/example1.crypt
bin/crypto d 12345678 examples/example1.crypt examples/example1.decrypt
diff examples/example1 examples/example1.decrypt
