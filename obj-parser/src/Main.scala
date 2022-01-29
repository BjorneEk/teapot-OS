package objparser

object Main:
	def main(args: Array[String]): Unit =
		if args.length < 2 then
			println("Expected usage: <file> <name>")
		else
			var n = false
			if(args.length > 2 && args(2) == "normal") then n = true
			val p = ObjParser("obj-files/" + args(0))
			val bobj = p.parseObject()
			bobj.writeAsC(args(1), "triangle3d_t", n);
