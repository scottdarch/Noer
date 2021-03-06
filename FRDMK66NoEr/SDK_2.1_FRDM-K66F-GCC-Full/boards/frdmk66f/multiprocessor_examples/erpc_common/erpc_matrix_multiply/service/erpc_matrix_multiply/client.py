#
# Generated by erpcgen 1.3.0 on Mon Sep  5 16:12:50 2016.
#
# AUTOGENERATED - DO NOT EDIT
#

import erpc
from . import common, interface

# Client for MatrixMultiplyService
class MatrixMultiplyServiceClient(interface.IMatrixMultiplyService):
    def __init__(self, manager):
        super(MatrixMultiplyServiceClient, self).__init__()
        self._clientManager = manager

    def erpcMatrixMultiply(self, matrix1, matrix2, result_matrix):
        assert type(result_matrix) is erpc.Reference, "out parameter must be a Reference object"

        # Build remote function invocation message.
        request = self._clientManager.create_request()
        outCodec = request.out_codec
        outCodec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.ERPCMATRIXMULTIPLY_ID,
                sequence=request.sequence))
        if matrix1 is None:
            raise ValueError("matrix1 is None")
        for _i0 in matrix1:
            for _i1 in _i0:
                outCodec.write_int32(_i1)


        if matrix2 is None:
            raise ValueError("matrix2 is None")
        for _i0 in matrix2:
            for _i1 in _i0:
                outCodec.write_int32(_i1)


        outCodec.end_write_message()

        # Send request and process reply.
        self._clientManager.perform_request(request)
        inCodec = request.in_codec
        result_matrix.value = []
        for _i0 in range(5):
            _v0 = []
            for _i1 in range(5):
                _v1 = inCodec.read_int32()
                _v0.append(_v1)

            result_matrix.value.append(_v0)

        inCodec.end_read_message()



