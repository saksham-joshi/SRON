>  NOTE: \
> In SRON's compiler, the implementation of the BytecodeWriter is not open sourced but everything else is. [ Hope you understand ]


## Import flow:

```bash
lib/_postfix_.hpp
     ^
     |
_base_writer_.hpp
     ^
     |
_utility_.hpp
     ^
     |
_attribute_writer_.hpp
     ^
     |
_data_savers_.hpp
     ^
     |
_specific_writers_.hpp
     ^
     |
_bytecode_writers_.hpp
```