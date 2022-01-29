package objparser



case class Vec3D(x : Double, y : Double, z : Double):

	lazy val length : Double = Math.sqrt(x*x + y*y + z*z)

	def normalized() : Vec3D = Vec3D(x / length, y / length, z / length)

	def crossProduct(v : Vec3D) : Vec3D = Vec3D(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		)
		
	def +(v : Vec3D) : Vec3D = Vec3D(x + v.x, y + v.y, z + v.z)
	def -(v : Vec3D) : Vec3D = Vec3D(x - v.x, y - v.y, z - v.z)
	def *(v : Vec3D) : Vec3D = Vec3D(x * v.x, y * v.y, z * v.z)
	def /(v : Vec3D) : Vec3D = Vec3D(x / v.x, y / v.y, z / v.z)
