import sys

headerFile = sys.argv[1]

print("[custom_script] Headers are generating using {}".format(__file__))

with open("{0}".format(headerFile), "a") as file:
    file.truncate(0)
    file.write("typedef enum TestEnum { NONE } TestTypedef;\n")
    file.close()
    print("[custom_script] Header whose name is {}, was generated".format(headerFile))

sys.exit(0)