# VaKiOS64 Operating System

VaKiOS64 is a simple x86 operating system that supports the following features:

- Interrupt Descriptor Table (IDT)
- Global Descriptor Table (GDT)
- Memory management
- Paging
- Programmable Interrupt Controller (PIC)
- Programmable Interval Timer (PIT)
- Simple standard input/output (stdio)

## Getting Started

### Prerequisites

To build and run VaKiOS64, you will need the following:

- A computer running Linux or macOS
- GCC cross-compiler for x86_64 
- GNU Make
- QEMU

### Building

To build VaKiOS64, clone the repository and run make:

```vbnet
git clone https://github.com/yourusername/VaKiOS64.git
cd VaKiOS64
./build.sh
```


This will create a file named `VaKiOS64.iso` in the `build` directory.

### Running

To run VaKiOS64 in QEMU, run the following command:

```vbnet
./qemu.sh
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

VaKiOS64 is released under the [MIT License](https://opensource.org/licenses/MIT). See `LICENSE` for details.
