# -*- coding: utf-8 -*-
from Connections import Connections
import re

dg = Connections( 'http://m.jizdnirady.cz/ConnMHD.aspx' )
a = dg.upcoming_departures( 'Dejvická' )

print( a )
