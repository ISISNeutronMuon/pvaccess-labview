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
			<Item Name="Probe.vi" Type="VI" URL="../examples/Probe.vi"/>
			<Item Name="Server.vi" Type="VI" URL="../examples/Server.vi"/>
		</Item>
		<Item Name="Test" Type="Folder">
			<Item Name="Generate PV Names.vi" Type="VI" URL="../source/Generate PV Names.vi"/>
			<Item Name="Generate Value.vi" Type="VI" URL="../source/Generate Value.vi"/>
			<Item Name="Test Client.vi" Type="VI" URL="../test/Test Client.vi"/>
			<Item Name="Test Server.vi" Type="VI" URL="../test/Test Server.vi"/>
		</Item>
		<Item Name="Utilities" Type="Folder">
			<Item Name="Get Library Path.vi" Type="VI" URL="../source/Get Library Path.vi"/>
		</Item>
		<Item Name=".vipb" Type="Document" URL="../.vipb"/>
		<Item Name=".vipc" Type="Document" URL="../.vipc"/>
		<Item Name="Client.lvlib" Type="Library" URL="../source/Client/Client.lvlib"/>
		<Item Name="Server.lvlib" Type="Library" URL="../source/Server/Server.lvlib"/>
		<Item Name="Value.lvlib" Type="Library" URL="../source/Value/Value.lvlib"/>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
