PLA parser
==========

The header ``<lorina/pla.hpp>`` implements methods to parse the PLA format.

The class :cpp:class:`lorina::pla_reader` provides the following public
member functions.

+----------------------------------------------+-------------------------------------------------------------------------+
| Function                                     | Description                                                             |
+==============================================+=========================================================================+
| ``on_number_of_inputs(number_of_inputs)``    | Callback method for parsed number of inputs                             |
+----------------------------------------------+-------------------------------------------------------------------------+
| ``on_number_of_outputs(number_of_outputs)``  | Callback method for parsed number of outputs                            |
+----------------------------------------------+-------------------------------------------------------------------------+
| ``on_number_of_terms(number_of_terms)``      | Callback method for parsed number of terms                              |
+----------------------------------------------+-------------------------------------------------------------------------+
| ``on_end()``                                 | Callback method for parsed end                                          |
+----------------------------------------------+-------------------------------------------------------------------------+
| ``on_term(term, out)``                       | Callback method for parsed term                                         |
+----------------------------------------------+-------------------------------------------------------------------------+

The following reader functions are available.

.. doc_overview_table:: namespacelorina
   :column: Function

   read_pla

.. doxygenfunction:: lorina::read_pla(std::istream&, const pla_reader&, diagnostic_engine *)
.. doxygenfunction:: lorina::read_pla(const std::string&, const pla_reader&, diagnostic_engine *)
