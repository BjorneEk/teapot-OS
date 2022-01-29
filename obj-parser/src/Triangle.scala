package objparser



case class Triangle(a : Vec3D, b : Vec3D, c : Vec3D, normal : Option[Vec3D] = None):

	def withNormal : Triangle = Triangle(a, b, c, Some((a - b).crossProduct(a - c).normalized()))
