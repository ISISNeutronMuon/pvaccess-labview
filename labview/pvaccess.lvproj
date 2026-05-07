<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="20008000">
	<Property Name="CCSymbols" Type="Str"></Property>
	<Property Name="NI.LV.All.SaveVersion" Type="Str">20.0</Property>
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Property Name="NI.Project.Description" Type="Str"></Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Examples" Type="Folder">
			<Item Name="Client Monitor.vi" Type="VI" URL="../examples/Client Monitor.vi"/>
			<Item Name="Client.vi" Type="VI" URL="../examples/Client.vi"/>
			<Item Name="Enum Client.vi" Type="VI" URL="../examples/Enum Client.vi"/>
			<Item Name="Enum Server.vi" Type="VI" URL="../examples/Enum Server.vi"/>
			<Item Name="Probe.vi" Type="VI" URL="../examples/Probe.vi"/>
			<Item Name="Server.vi" Type="VI" URL="../examples/Server.vi"/>
			<Item Name="Simple Client.vi" Type="VI" URL="../examples/Simple Client.vi"/>
			<Item Name="Simple Server.vi" Type="VI" URL="../examples/Simple Server.vi"/>
		</Item>
		<Item Name="Packaging" Type="Folder">
			<Item Name="pvaccess.vipb" Type="Document" URL="../pvaccess.vipb"/>
		</Item>
		<Item Name="Test" Type="Folder">
			<Item Name="Every Type Code.ctl" Type="VI" URL="../test/Every Type Code.ctl"/>
			<Item Name="Every Value.vi" Type="VI" URL="../test/Every Value.vi"/>
			<Item Name="Test Client.vi" Type="VI" URL="../test/Test Client.vi"/>
			<Item Name="Test Server.vi" Type="VI" URL="../test/Test Server.vi"/>
			<Item Name="Type Code to String.vi" Type="VI" URL="../test/Type Code to String.vi"/>
		</Item>
		<Item Name="PV Access.lvlib" Type="Library" URL="../source/PV Access.lvlib"/>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
