<?hh

/**
 * Needed Libraries
 */
require_once('array_is_associative.hh');
require_once('array_to_map.hh');
require_once('array_to_vector.hh');

/**
 * This method converts a sequential array to a vector
 * @name array_to_vector()
 * @param array<int, mixed> $arrData
 * @return Vector<mixed>
 */
function array_to_vector(array $arrData) : Vector<mixed>
{
	// Set the return variable
	$vecReturn = Vector {};
	// Iterate over the array
	foreach ($arrData as $intIndex => $mixValue) {
		// Check the value
		if (is_array($mixValue) && array_is_associative($mixValue)) {
			// Set the value
			$vecReturn->add(array_to_map($mixValue));
		} elseif (is_array($mixValue)) {
			// Set the value
			$vecReturn->add(array_to_vector($mixValue));
		} else {
			// Set the value
			$vecReturn->add($mixValue);
		}
	}
	// Return the vector
	return $vecReturn;
}
