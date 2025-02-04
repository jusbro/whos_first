# Who's First - High School Jeopardy Machine

Welcome to the "Who's First" project – an Arduino retrofit of a high school Jeopardy machine designed for interactive classroom activities. The Arduinos are used to replace broken hardware in the provided Who's First Device. This project aims to enhance engagement and learning in a classroom setting, allowing students to participate in a Jeopardy-style game to test their knowledge.

## Overview

The "Whose First" project consists of two main components: a transmitter and a receiver. The transmitter acts as a buzzer system for students to "ring in" their answers, while the receiver processes and displays the results.

## Features

- **Buzzer System:** Students can use the transmitter as a buzzer to quickly answer questions.
- **Wireless Communication:** The NRF24L01 modules enable seamless wireless communication between the transmitter and receiver.
- **Arduino-Based:** The project is implemented using Arduino Uno boards, making it accessible and customizable.
- **Student-Built PCBs and programmed hardware.

## Getting Started

### Transmitter Setup

1. Connect the NRF24L01 module to the Arduino Nano Every on the transmitter side.
2. Upload the provided transmitter code to the Arduino board.
   

### Receiver Setup

1. Connect the NRF24L01 module to the Arduino Uno on the receiver side.
2. Upload the provided receiver code to the Arduino board.
3. Ensure that the addresses in both transmitter and receiver are configured correctly.

## Usage

1. Power on both the transmitter and receiver.
2. Ask questions in the classroom, and students can ring in their answers using the transmitter.
3. The receiver displays the order in which students rang in and provides an interactive experience for the class.
4. The reset button on the reciever is pressed to restart the process at the end of each question

## Contributing

Contributions to the project are welcome! If you have suggestions, improvements, or bug fixes, please open an issue or submit a pull request.

## License

MIT License

Copyright (c) 2024 Justin Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Acknowledgments

- The project utilizes the NRF24L01 library for wireless communication.
- Special thanks to the Arduino community for their valuable resources and support.

If you have any questions or need assistance, feel free to reach out.
