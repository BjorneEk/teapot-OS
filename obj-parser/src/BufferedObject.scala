package objparser

import java.io.{File, FileWriter}

class BufferedObject(mesh : Vector[Triangle]):

	def writeAsC(name : String, triName : String = "", withNormal : Boolean = false) : Unit =


		var newMesh = mesh;
		if withNormal then newMesh = (for t <- mesh yield t.withNormal).toVector

		val writer = new FileWriter("dest/" + name + ".c");

		writer.write("/**\n *   Generated code\n *\n *   @author Gustaf Franzén :: https://github.com/BjorneEk;\n *\n **/\n\n")
		writer.write("#define " + name.toUpperCase + "_LENGTH " + newMesh.length + "\n\n")
		writer.write(s"$triName $name[] = {\n")
		/// {.p1={-0.5f, -0.5f, -0.5f,  1.0f}, .p2={-0.5f,  0.5f, -0.5f,  1.0f}, .p3={ 0.5f, -0.5f, -0.5f,  1.0f}}
		if withNormal then
			for t <- newMesh do
				writer.write(s"\t{.p1={${t.a.x}f, ${t.a.y}f, ${t.a.z}f}, .p2={${t.b.x}f, ${t.b.y}f, ${t.b.z}f}, .p3={${t.c.x}f, ${t.c.y}f, ${t.c.z}f}, .normal={${t.normal.get.x}f, ${t.normal.get.y}f, ${t.normal.get.z}f}},\n")
		else
			for t <- newMesh do
				writer.write(s"\t{.p1={${t.a.x}f, ${t.a.y}f, ${t.a.z}f}, .p2={${t.b.x}f, ${t.b.y}f, ${t.b.z}f}, .p3={${t.c.x}f, ${t.c.y}f, ${t.c.z}f}},\n")
		writer.write(s"};\n")
		writer.write("/**\n *   End of generated code\n **/")
		writer.close();
