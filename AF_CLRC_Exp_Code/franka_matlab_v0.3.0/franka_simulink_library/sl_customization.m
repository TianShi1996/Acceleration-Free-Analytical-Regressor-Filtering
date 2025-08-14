%  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function sl_customization(cm)
    cm.ExtModeTransports.add('franka_emika_panda.tlc', 'tcpip', 'ext_comm', 'Level1');
    cm.ExtModeTransports.add('franka_emika_panda.tlc', 'XCP on TCP/IP', 'ext_xcp', 'Level2 - Open');
end