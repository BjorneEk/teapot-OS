package objparser

import java.io.File
import java.util.Scanner
import collection.mutable.ArrayBuffer

class ObjParser(s : Scanner):
	import ObjParser._

	/**
	 *  convert a line with information about a face into
	 *  a instance of Face with integer data
	 **/
	private def readFace(s : String) : Face =
		val ints = (for i <- s.split(' ').filter(_ != "") yield i.toInt);
		if ints.length > 3 then
			println("WARNING, a face that is not a triangle has been detected")
		Face(ints(0), ints(1), ints(2))

	/**
	 *  convert a line with information about a vertex into
	 *  a instance of Vec3D containing the vertex data
	 **/
	private def readVector(s : String) : Vec3D =
		val dubs = for i <- s.split(' ').filter(_ != "") yield i.toDouble
		if dubs.length > 3 then
			println("WARNING, error reading avector")
		Vec3D(dubs(0), dubs(1), dubs(2))

	/**
	 *  create a mesh by replacing faces with triangles
	 *  whith correct vertecies
	 **/
	private def constructMesh(vecs : Vector[Vec3D], faces : Vector[Face]) : Vector[Triangle] =
		(for f <- faces yield Triangle(vecs(f.a-1), vecs(f.b-1), vecs(f.c-1))).toVector


	/**
	 *  parse a .obj file whith triangle faces
	 *  and no normal data into a mesh of triangles
	 **/
	def parseObject() : BufferedObject =
		val vectors = new ArrayBuffer[Vec3D]()
		val faces   = new ArrayBuffer[Face]()
		while(s.hasNext()) do
			val line = s.nextLine().trim
			if line.length > 1 then
				if      line(0) == 'f' then
					faces += readFace(line.substring(1))
				else if line(0) == 'v' then
					vectors += readVector(line.substring(1))
		BufferedObject(constructMesh(vectors.toVector, faces.toVector))

object ObjParser:

	def apply(filename : String) : ObjParser = new ObjParser(Scanner(File(filename)))
	case class Face(a : Int, b : Int, c : Int)
