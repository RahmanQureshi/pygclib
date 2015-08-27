class GalilMotionController:

	def __init__(self, address = "10.10.1.21 -d"):
		import gclib
		from requests.exceptions import ConnectionError
		import atexit
		rc, self.con = gclib.GOpen(address)
		self.countspermm = 629.8
		self.countsperdeg = 889
		if (rc!=0):
			raise ConnectionError("Unable to open connection to controller")
		atexit.register(self.close)
		gclib.GCommand(self.con, 'SH') # enable moving


	def close(self):
		import gclib
		gclib.GClose(self.con)

	def move(self, axis, speed, displacement, blocking=True):
		import gclib
		import time
		"""Move the specified axis a certain displacement at a certain speed

		Args:
            :param axis (str): A B C or X Y Z
            :param speed (int): speed to move in mm/s
            :param displacement (int): displacement in mm
            :param blocking (bool): prevents method from returning until motion controller is in next position
		"""
		rc0, init_pos = gclib.GCommand(self.con, 'TP'+axis)
		rc1 = gclib.GCommand(self.con, 'SP'+axis+'='+str(round(speed* self.countspermm)))
		rc2 = gclib.GCommand(self.con, 'IP'+axis+'='+str(round(displacement* self.countspermm)))

		if blocking:
			time.sleep(0.2) # allow motors to speed up
		while(blocking):
			rc, cur_speed = gclib.GCommand(self.con, 'TV'+axis)
			if int(cur_speed[0:-2].strip().split('.')[0]) == 0:
				break
		return (rc1, rc2)


	def rotate(self, degrees_per_sec, degrees, blocking=True):
		import gclib
		import time

		rc1 = gclib.GCommand(self.con, 'SPW='+str(round(degrees_per_sec*self.countsperdeg)))
		rc2 = gclib.GCommand(self.con, 'IPW='+str(round(degrees*self.countsperdeg)))

		# Due to the inaccuracies of our turntable, a different blocking method will be implemented
		# Ideally one would use displacement-time integral for stability assessment

		if blocking:
			time.sleep(0.2) # allow motors to speed up
		while(blocking):
			rc, cur_speed = gclib.GCommand(self.con, 'TVW')
			if int(cur_speed[0:-2].strip().split('.')[0]) == 0:
				break
		return rc1, rc2

_gmc = GalilMotionController()
move = _gmc.move
rotate = _gmc.rotate