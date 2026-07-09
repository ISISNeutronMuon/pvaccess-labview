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
			<Item Name="User Defined Type (Class)" Type="Folder">
				<Item Name="Custom Structure.ctl" Type="VI" URL="../examples/Custom Structure.ctl"/>
				<Item Name="My Custom Type.lvclass" Type="LVClass" URL="../examples/My Custom Type/My Custom Type.lvclass"/>
				<Item Name="User Defined Type Class Server.vi" Type="VI" URL="../examples/User Defined Type Class Server.vi"/>
			</Item>
			<Item Name="Client Monitor.vi" Type="VI" URL="../examples/Client Monitor.vi"/>
			<Item Name="Client.vi" Type="VI" URL="../examples/Client.vi"/>
			<Item Name="Enum Client.vi" Type="VI" URL="../examples/Enum Client.vi"/>
			<Item Name="Enum Server.vi" Type="VI" URL="../examples/Enum Server.vi"/>
			<Item Name="Probe.vi" Type="VI" URL="../examples/Probe.vi"/>
			<Item Name="Server.vi" Type="VI" URL="../examples/Server.vi"/>
			<Item Name="Simple Client.vi" Type="VI" URL="../examples/Simple Client.vi"/>
			<Item Name="Simple Server.vi" Type="VI" URL="../examples/Simple Server.vi"/>
			<Item Name="User Defined Type Server.vi" Type="VI" URL="../examples/User Defined Type Server.vi"/>
		</Item>
		<Item Name="Libraries" Type="Folder">
			<Item Name="linux-x86_64" Type="Folder" URL="../libraries/linux-x86_64">
				<Property Name="NI.DISK" Type="Bool">true</Property>
			</Item>
			<Item Name="windows-x64" Type="Folder" URL="../libraries/windows-x64">
				<Property Name="NI.DISK" Type="Bool">true</Property>
			</Item>
			<Item Name="pvaccess-errors.txt" Type="Document" URL="../errors/pvaccess-errors.txt"/>
		</Item>
		<Item Name="Packaging" Type="Folder">
			<Item Name="pvaccess.vipb" Type="Document" URL="../pvaccess.vipb"/>
		</Item>
		<Item Name="Test" Type="Folder">
			<Item Name="Every Type Code.ctl" Type="VI" URL="../test/Every Type Code.ctl"/>
			<Item Name="Every Value.vi" Type="VI" URL="../test/Every Value.vi"/>
			<Item Name="Generate Value.vi" Type="VI" URL="../test/Generate Value.vi"/>
			<Item Name="Test Client.vi" Type="VI" URL="../test/Test Client.vi"/>
			<Item Name="Test Server.vi" Type="VI" URL="../test/Test Server.vi"/>
			<Item Name="Test Simple Client.vi" Type="VI" URL="../test/Test Simple Client.vi"/>
			<Item Name="Test Simple Server.vi" Type="VI" URL="../test/Test Simple Server.vi"/>
			<Item Name="Type Code to String.vi" Type="VI" URL="../test/Type Code to String.vi"/>
		</Item>
		<Item Name="PV Access.lvlib" Type="Library" URL="../source/PV Access.lvlib"/>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="Source Distribution" Type="Source Distribution">
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{00E0BD19-D0FF-434D-92BD-7E6267BEF352}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Source Distribution</Property>
				<Property Name="Bld_excludedDirectory[0]" Type="Path">vi.lib</Property>
				<Property Name="Bld_excludedDirectory[0].pathType" Type="Str">relativeToAppDir</Property>
				<Property Name="Bld_excludedDirectory[1]" Type="Path">resource/objmgr</Property>
				<Property Name="Bld_excludedDirectory[1].pathType" Type="Str">relativeToAppDir</Property>
				<Property Name="Bld_excludedDirectory[2]" Type="Path">/C/ProgramData/National Instruments/InstCache/25.0</Property>
				<Property Name="Bld_excludedDirectory[3]" Type="Path">/C/Users/eyw68381/OneDrive - Science and Technology Facilities Council/Documents/LabVIEW Data/2025(64-bit)/ExtraVILib</Property>
				<Property Name="Bld_excludedDirectory[4]" Type="Path">instr.lib</Property>
				<Property Name="Bld_excludedDirectory[4].pathType" Type="Str">relativeToAppDir</Property>
				<Property Name="Bld_excludedDirectory[5]" Type="Path">user.lib</Property>
				<Property Name="Bld_excludedDirectory[5].pathType" Type="Str">relativeToAppDir</Property>
				<Property Name="Bld_excludedDirectoryCount" Type="Int">6</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../build/labview</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{A8D6EAE3-F668-4BA8-B98D-987811F628C7}</Property>
				<Property Name="Bld_removeVIObj" Type="Int">2</Property>
				<Property Name="Bld_version.build" Type="Int">12</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Destination Directory</Property>
				<Property Name="Destination[0].path" Type="Path">../build/labview</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../build/labview/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{93883F78-19D2-4999-8878-0A752227FDD9}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Client.lvlib/Client.lvclass/Close.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[10].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[10].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Server.lvlib/Server.lvclass/Post.vi</Property>
				<Property Name="Source[10].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[10].type" Type="Str">VI</Property>
				<Property Name="Source[11].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[11].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Server.lvlib/Server.lvclass/Start.vi</Property>
				<Property Name="Source[11].preventRename" Type="Bool">true</Property>
				<Property Name="Source[11].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[11].type" Type="Str">VI</Property>
				<Property Name="Source[12].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[12].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Server.lvlib/Server.lvclass/Stop.vi</Property>
				<Property Name="Source[12].preventRename" Type="Bool">true</Property>
				<Property Name="Source[12].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[12].type" Type="Str">VI</Property>
				<Property Name="Source[13].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[13].itemID" Type="Ref">/My Computer/PV Access.lvlib/PV Data.lvlib/Create.vi</Property>
				<Property Name="Source[13].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[13].type" Type="Str">VI</Property>
				<Property Name="Source[14].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[14].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[14].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[14].itemID" Type="Ref">/My Computer/Examples</Property>
				<Property Name="Source[14].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[14].type" Type="Str">Container</Property>
				<Property Name="Source[15].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[15].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[15].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[15].itemID" Type="Ref">/My Computer/Libraries</Property>
				<Property Name="Source[15].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[15].type" Type="Str">Container</Property>
				<Property Name="Source[16].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[16].itemID" Type="Ref">/My Computer/Libraries/pvaccess-errors.txt</Property>
				<Property Name="Source[16].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Client.lvlib/Client.lvclass/Create.vi</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Client.lvlib/Client.lvclass/Get.vi</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">VI</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Client.lvlib/Client.lvclass/Monitor.vi</Property>
				<Property Name="Source[4].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[4].type" Type="Str">VI</Property>
				<Property Name="Source[5].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[5].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Client.lvlib/Client.lvclass/Put.vi</Property>
				<Property Name="Source[5].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[5].type" Type="Str">VI</Property>
				<Property Name="Source[6].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[6].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Server.lvlib/Server.lvclass/Add PV.vi</Property>
				<Property Name="Source[6].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[6].type" Type="Str">VI</Property>
				<Property Name="Source[7].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[7].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Server.lvlib/Server.lvclass/Close.vi</Property>
				<Property Name="Source[7].preventRename" Type="Bool">true</Property>
				<Property Name="Source[7].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[7].type" Type="Str">VI</Property>
				<Property Name="Source[8].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[8].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Server.lvlib/Server.lvclass/Create.vi</Property>
				<Property Name="Source[8].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[8].type" Type="Str">VI</Property>
				<Property Name="Source[9].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[9].itemID" Type="Ref">/My Computer/PV Access.lvlib/PVA Server.lvlib/Server.lvclass/Fetch.vi</Property>
				<Property Name="Source[9].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[9].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">17</Property>
			</Item>
		</Item>
	</Item>
</Project>
