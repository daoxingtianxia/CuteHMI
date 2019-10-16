import qbs

import cutehmi

Project {
	name: "CuteHMI.Examples.Modbus.Requests.0"

	cutehmi.Extension {
		type: []

		name: parent.name

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Modbus Requests Example"

		description: "Example demonstrating a variety of Modbus requests."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
         "DeviceControl.qml",
         "DiagnosticsControl.qml",
         "FetchCommEventCounterControl.qml",
         "FetchCommEventLogControl.qml",
         "LICENSE",
         "Main.qml",
         "MaskWrite4xRegisterControl.qml",
         "README.md",
         "ReadCoilsControl.qml",
         "ReadDiscreteInputsControl.qml",
         "ReadExceptionStatusControl.qml",
         "ReadFIFOQueueControl.qml",
         "ReadFileRecordControl.qml",
         "ReadHoldingRegistersControl.qml",
         "ReadInputRegistersControl.qml",
         "ReadWriteMultipleHoldingRegistersControl.qml",
         "ReportSlaveIdControl.qml",
         "TCPClientConfiguration.qml",
         "TCPServerConfiguration.qml",
         "WriteCoilControl.qml",
         "WriteDiscreteInputControl.qml",
         "WriteFileRecordControl.qml",
         "WriteHoldingRegisterControl.qml",
         "WriteInputRegisterControl.qml",
         "WriteMultipleCoilsControl.qml",
         "WriteMultipleDiscreteInputsControl.qml",
         "WriteMultipleHoldingRegistersControl.qml",
         "WriteMultipleInputRegistersControl.qml",
     ]

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi_view" }

		Depends { name: "CuteHMI.Modbus.2" }
	}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: The MIT License
//(c)MP: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)MP: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)MP: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
