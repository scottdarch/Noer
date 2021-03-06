#
# Generated by erpcgen 1.3.0 on Mon Sep  5 16:12:50 2016.
#
# AUTOGENERATED - DO NOT EDIT
#

import erpc
from . import common, interface

# Client for MatrixMultiplyService
class MatrixMultiplyServiceService(erpc.server.Service):
    def __init__(self, handler):
        super(MatrixMultiplyServiceService, self).__init__(interface.IMatrixMultiplyService.SERVICE_ID)
        self._handler = handler
        self._methods = {
                interface.IMatrixMultiplyService.ERPCMATRIXMULTIPLY_ID : self._handle_erpcMatrixMultiply,
            }

    def _handle_erpcMatrixMultiply(self, sequence, inCodec, outCodec):
        # Create reference objects to pass into handler for out/inout parameters.
        result_matrix = erpc.Reference()

        # Read incoming parameters.
        matrix1 = []
        for _i0 in range(5):
            _v0 = []
            for _i1 in range(5):
                _v1 = inCodec.read_int32()
                _v0.append(_v1)

            matrix1.append(_v0)

        matrix2 = []
        for _i0 in range(5):
            _v0 = []
            for _i1 in range(5):
                _v1 = inCodec.read_int32()
                _v0.append(_v1)

            matrix2.append(_v0)

        inCodec.end_read_message()

        # Invoke user implementation of remote function.
        _result = self._handler.erpcMatrixMultiply(matrix1, matrix2, result_matrix)

        # Construct reply message.
        outCodec.start_write_message(erpc.codec.MessageInfo(
            type=erpc.codec.MessageType.kReplyMessage,
            service=interface.IMatrixMultiplyService.SERVICE_ID,
            request=interface.IMatrixMultiplyService.ERPCMATRIXMULTIPLY_ID,
            sequence=sequence))
        if result_matrix.value is None:
            raise ValueError("result_matrix is None")
        for _i0 in result_matrix.value:
            for _i1 in _i0:
                outCodec.write_int32(_i1)


        outCodec.end_write_message()


