<?hh

///////////////////////////////////////////////////////////////////////////////
/// Enumerations /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/**
 * This enumeration contains the various data types
 * @enum
 * @name Type {}
 * @var enum<string>
 */
enum Type : string
{
	VArray    = 'array';
	VBinary   = 'binary';
	VBoolean  = 'boolean';
	VCallable = 'callable';
	VCustom   = 'custom';
	VDouble   = 'double';
	VFloat    = 'float';
	VInteger  = 'integer';
	VJson     = 'json';
	VMap      = 'HH\Map';
	VNull     = 'NULL';
	VNumeric  = 'numeric';
	VPair     = 'HH\Pair';
	VObject   = 'object';
	VResource = 'resource';
	VSCalar   = 'scalar';
	VSet      = 'HH\Set';
	VString   = 'string';
	VUnknown  = 'unknown type';
	VVector   = 'HH\Vector';
};

///////////////////////////////////////////////////////////////////////////////
/// Variant Class Definition /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class Variant
{
	//////////////////////////////////////////////////////////////////////////////
	/// Properties //////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This property contains the conversion map for the different types
	 * @access protected
	 * @name Variant::$mConversionMap
	 * @var Map<Type, Vector<Type>>
	 */
	protected Map<Type, Vector<Type>> $mConversionMap = Map {
		Type::VArray    => Vector { Type::VJson, Type::VMap, Type::VNull, Type::VObject, Type::VPair, Type::VSet, Type::VVector },
		Type::VBinary   => Vector { Type::VNull, Type::VString },
		Type::VBoolean  => Vector { Type::VDouble, Type::VFloat, Type::VInteger, Type::VNull, Type::VString },
		Type::VCallable => Vector { Type::VNull },
		Type::VDouble   => Vector { Type::VBoolean, Type::VFloat, Type::VInteger, Type::VNull, Type::VString },
		Type::VFloat    => Vector { Type::VBoolean, Type::VDouble, Type::VInteger, Type::VNull, Type::VString },
		Type::VInteger  => Vector { Type::VBoolean, Type::VDouble, Type::VFloat, Type::VNull, Type::VString },
		Type::VJson     => Vector { Type::VArray, Type::VMap, Type::VNull, Type::VObject, Type::VPair, Type::VSet, Type::VVector },
		Type::VMap      => Vector { Type::VArray, Type::VJson, Type::VNull, Type::VSet, Type::VVector },
		Type::VNull     => Vector { Type::VBoolean, Type::VInteger, Type::VString },
		Type::VPair     => Vector { Type::VArray, Type::VJson, Type::VMap, Type::VNull, Type::VSet, Type::VVector },
		Type::VObject   => Vector { Type::VArray, Type::VJson, Type::VMap },
		Type::VResource => Vector { Type::VNull },
		Type::VSet      => Vector { Type::VArray, Type::VJson, Type::VNull, Type::VVector },
		Type::VString   => Vector { Type::VBinary, Type::VBoolean, Type::VDouble, Type::VFloat, Type::VInteger, Type::VNull },
		Type::VUnknown  => Vector { Type::VNull },
		Type::VVector   => Vector { Type::VArray, Type::VJson, Type::VMap, Type::VNull, Type::VSet }
	};

	/**
	 * This property contains the actual data for the class
	 * @access protected
	 * @name Variant::$mData
	 * @var mixed
	 */
	protected mixed $mData                            = null;

	/**
	 * This property contains the reserved instance types
	 * @access protected
	 * @name Variant::$mInstanceTypes
	 * @var HH\Vector<Type>
	 */
	protected Vector<Type> $mInstanceTypes            = Vector {
		Type::VMap, Type::VPair, Type::VSet, Type::VVector
	};

	/**
	 * This map contains the true null type for each variant type
	 * @access protected
	 * @name Variant::$mNullTypes
	 * @var Map<Type, mixed>
	 */
	protected Map<Type, mixed> $mNullTypes            = Map {
		Type::VArray    => [],
		Type::VBinary   => null,
		Type::VBoolean  => false,
		Type::VCallable => null,
		Type::VDouble   => 0.0,
		Type::VFloat    => 0.0,
		Type::VInteger  => 0,
		Type::VJson     => '{}',
		Type::VMap      => Map {},
		Type::VNull     => null,
		Type::VPair     => Pair {null, null},
		Type::VObject   => null,
		Type::VResource => null,
		Type::VSet      => Set {},
		Type::VString   => '',
		Type::VVector   => Vector {}
	};

	/**
	 * This property contains the numeric types
	 * @access protected
	 * @name Variant::$mNumericTypes
	 * @var HH\Vector<Type>
	 */
	protected Vector<Type> $mNumericTypes             = Vector {
		Type::VDouble, Type::VFloat, Type::VInteger
	};

	/**
	 * This property contains all of the scalar types
	 * @access protected
	 * @name Variant::$mScalarTypes
	 * @var HH\Vector<Type>
	 */
	protected Vector<Type> $mScalarTypes              = Vector {
		Type::VBoolean, Type::VDouble, Type::VFloat, Type::VInteger, Type::VString
	};

	//////////////////////////////////////////////////////////////////////////////
	/// Constructor /////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method sets up the class with some data
	 * @access public
	 * @name Variant::Variant()
	 * @param mixed $mixData [null]
	 * @return Variant
	 */
	public function __construct(mixed $mixData = null) : Variant
	{
		// Check for an associative array or map
		if ((is_array($mixData) && boolval(count(array_filter(array_keys($mixData))))) || ($mixData instanceof Map)) {
			// Return a new VariantMap
			return new VariantMap($mixData);
		}
		// Check for a sequential array or vector
		if ((is_array($mixData) && (boolval(count(array_filter(array_keys($mixData)))) === false)) || ($mixData instanceof Map)) {
			// Return a new VariantList
			return new VariantList($mixData);
		}
		// Set the data into the instance
		$this->mData = $mixData;
		// Return the instance
		return $this;
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Static Constructor //////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method instantiates and sets up the class with some data
	 * @access public
	 * @name Variant::Factory()
	 * @param mixed $mixData [null]
	 * @return Variant self
	 * @static
	 */
	public static function Factory(mixed $mixData = null) : Variant
	{
		// Return the instance
		return new self($mixData);
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Magic Methods ///////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method provides a magic string conversion for the class
	 * @access public
	 * @name Variant::__toString()
	 * @return string
	 */
	public function __toString() : string
	{
		// Return the string conversion
		return $this->toString();
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ///////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method converts an array to it's target type
	 * @access protected
	 * @name Variant::arrayTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function arrayTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VJson   : return json_encode($this->mData); break; // JSON
			case Type::VMap    : return new Map($this->mData);     break; // HH\Map
			case Type::VNull   : return null;                      break; // null
			case Type::VObject : return (object) $this->mData;     break; // stdClass
			case Type::VPair   : return new Pair($this->mData);    break; // HH\Pair
			case Type::VSet    : return new Set($this->mData);     break; // HH\Set
			case Type::VVector : return new Vector($this->mData);  break; // HH\Vector
		}
	}

	/**
	 * This method converts binary to the target type
	 * @access protected
	 * @name Variant::binaryTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function binaryTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VNull   : return null;                  break; // null
			case Type::VString : return (string) $this->mData; break; // string
		}
	}

	/**
	 * This method converts a boolean to the target type
	 * @access protected
	 * @name Variant::booleanTo()
	 * @param Type $targetType
	 * @return mixed
	 */
	protected function booleanTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VDouble  : return doubleval($this->mData); break; // double
			case Type::VFloat   : return floatval($this->mData);  break; // float
			case Type::VInteger : return intval($this->mData);    break; // integer
			case Type::VNull    : return null;                    break; // null
			case Type::VString  : return (string) $this->mData;   break; // string
		}
	}

	/**
	 * This method converts a callable to the target type
	 * @access protected
	 * @name Variant::callableTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function callableTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VNull : return null; break; // null
		}
	}

	/**
	 * This method converts a double to the target type
	 * @access protected
	 * @name Variant::doubleTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function doubleTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VBoolean : return boolval($this->mData);  break; // boolean
			case Type::VFloat   : return floatval($this->mData); break; // float
			case Type::VInteger : return intval($this->mData);   break; // integer
			case Type::VNull    : return null;                   break; // null
			case Type::VString  : return (string) $this->mData;  break; // string
		}
	}

	/**
	 * This method converts a float to the target type
	 * @access protected
	 * @name Variant::floatTo()
	 * @param Type $targetType
	 * @return mixed
	 */
	protected function floatTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VBoolean : return boolval($this->mData);   break; // boolean
			case Type::VDouble  : return doubleval($this->mData); break; // double
			case Type::VInteger : return intval($this->mData);    break; // integer
			case Type::VNull    : return null;                    break; // null
			case Type::VString  : return (string) $this->mData;   break; // string
		}
	}

	/**
	 * This method converts an integer to the target type
	 * @access protected
	 * @name Variant::integerTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function integerTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VBoolean : return boolval($this->mData);   break; // boolean
			case Type::VDouble  : return doubleval($this->mData); break; // double
			case Type::VFloat   : return floatval($this->mData);  break; // float
			case Type::VNull    : return null;                    break; // null
			case Type::VString  : return (string) $this->mData;   break; // string
		}
	}

	/**
	 * This method converts a json string to the target type
	 * @access protected
	 * @name Variant::jsonTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function jsonTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VArray  : return json_decode($this->mData, true);             break; // array
			case Type::VMap    : return new Map(json_decode($this->mData,    true)); break; // HH\Map
			case Type::VNull   : return null;                                        break; // null
			case Type::VObject : return json_decode($this->mData);                   break; // stdClass
			case Type::VPair   : return new Pair(json_decode($this->mData,   true)); break; // HH\Pair
			case Type::VSet    : return new Set(json_decode($this->mData,    true)); break; // HH\Set
			case Type::VVector : return new Vector(json_decode($this->mData, true)); break; // HH\Vector
		}
	}

	/**
	 * This method converts a map to the target type
	 * @access protected
	 * @name Variant::mapTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function mapTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VArray  : return $this->mData->toArray();   break; // array
			case Type::VJson   : return json_encode($this->mData); break; // json
			case Type::VNull   : return null;                      break; // null
			case Type::VSet    : return $this->mData->toSet();     break; // HH\Set
			case Type::VVector : return $this->mData->toVector();  break; // HH\Vector
		}
	}

	/**
	 * This method converts a null to the target type
	 * @access protected
	 * @name Variant::nullTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function nullTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VBoolean : return boolval($this->mData); break; // boolean
			case Type::VInteger : return intval($this->mData);  break; // integer
			case Type::VString  : return (string) $this->mData; break; // string
		}
	}

	/**
	 * This method converts a pair to the target type
	 * @access protected
	 * @name Variant::pairTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function pairTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VArray  : return $this->mData->toArray();   break; // array
			case Type::VJson   : return json_encode($this->mData); break; // json
			case Type::VMap    : return $this->mData->toMap();     break; // HH\Map
			case Type::VNull   : return null;                      break; // null
			case Type::VSet    : return $this->mData->toSet();     break; // HH\Set
			case Type::VVector : return $this->mData->toVector();  break; // HH\Vector
		}
	}

	/**
	 * This method converts an object to the target type
	 * @access protected
	 * @name Variant::objectTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function objectTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VArray : return (array) $this->mData;      break;     // array
			case Type::VJson  : return json_encode($this->mData); break;     // json
			case Type::VMap   : return new Map((array) $this->mData); break; // HH\Map
		}
	}

	/**
	 * This method converts a resource to the target type
	 * @access protected
	 * @name Variant::resourceTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function resourceTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VNull : return null; break; // null
		}
	}

	/**
	 * This method converts a set to the target type
	 * @access protected
	 * @name Variant::setTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function setTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VArray  : return $this->mData->toArray();   break; // array
			case Type::VJson   : return json_encode($this->mData); break; // json
			case Type::VNull   : return null;                      break; // null
			case Type::VVector : return $this->mData->toVector();  break; // HH\Vector
		}
	}

	/**
	 * This method converts a string to the target type
	 * @access protected
	 * @name Variant::stringTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function stringTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VBinary  : return (binary) $this->mData;   break; // binary
			case Type::VBoolean : return boolval($this->mData);   break; // boolean
			case Type::VDouble  : return doubleval($this->mData); break; // double
			case Type::VFloat   : return floatval($this->mData);  break; // float
			case Type::VInteger : return intval($this->mData);    break; // integer
			case Type::VNull    : return null;                    break; // null
		}
	}

	/**
	 * This method converts an unkown type to the target type
	 * @access protected
	 * @name Variant::unknownType()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function unknownTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VNull : return null; break; // null
		}
	}

	/**
	 * This method converts a vector to the target type
	 * @access protected
	 * @name Variant::vectorTo()
	 * @param Type $typeTarget
	 * @return mixed
	 */
	protected function vectorTo(Type $typeTarget) : mixed
	{
		// Determine the target type
		switch ($typeTarget) {
			case Type::VArray : return $this->mData->toArray();   break; // array
			case Type::VJson  : return json_encode($this->mData); break; // json
			case Type::VMap   : return $this->mData->toMap();     break; // HH\Map
			case Type::VNull  : return null;                      break; // null
			case Type::VSet   : return $this->mData->toSet();     break; // HH\Set
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Public Methods //////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method determines whether or not the data can be converted to a specified type
	 * @access public
	 * @name Variant::can()
	 * @param Type $typeTarget
	 * @return bool
	 */
	public function can(Type $typeTarget) : bool
	{
		// Check the type
		if ($this->mConversionMap->get($this->getType())->linearSearch($typeTarget) !== -1) {
			// A conversion is possible
			return true;
		}
		// No conversion possible at this time
		return false;
	}

	/**
	 * This method converts the data to a specified target type
	 * @access public
	 * @name Variant::convert()
	 * @return mixed
	 */
	public function convert(Type $typeTarget) : mixed
	{
		// Check the type
		if ($this->getType() === $typeTarget) {
			// Return the data
			return $this->mData;
		}
		// Check to see if we can convert
		if ($this->can($typeTarget)) {
			// Determine the source type
			switch ($this->getType()) {
				case Type::VArray    : return $this->arrayTo($typeTarget);    break; // array
				case Type::VBinary   : return $this->binaryTo($typeTarget);   break; // binary
				case Type::VBoolean  : return $this->booleanTo($typeTarget);  break; // boolean
				case Type::VCallable : return $this->callableTo($typeTarget); break; // callable
				case Type::VDouble   : return $this->doubleTo($typeTarget);   break; // double
				case Type::VFloat    : return $this->floatTo($typeTarget);    break; // float
				case Type::VInteger  : return $this->integerTo($typeTarget);  break; // integer
				case Type::VJson     : return $this->jsonTo($typeTarget);     break; // json
				case Type::VMap      : return $this->mapTo($typeTarget);      break; // HH\Map
				case Type::VNull     : return $this->nullTo($typeTarget);     break; // null
				case Type::VPair     : return $this->pairTo($typeTarget);     break; // HH\Pair
				case Type::VObject   : return $this->objectTo($typeTarget);   break; // stdClass
				case Type::VResource : return $this->resourceTo($typeTarget); break; // resource
				case Type::VSet      : return $this->setTo($typeTarget);      break; // HH\Set
				case Type::VString   : return $this->stringTo($typeTarget);   break; // string
				case Type::VUnknown  : return $this->unknownTo($typeTarget);  break; // unknown type
				case Type::VVector   : return $this->vectorTo($typeTarget);   break; // HH\Vector
			}
		} else {
			// We cannot convert to this type, we're done
			return $this->mNullTypes->get($typeTarget);
		}
	}

	/**
	 * This method determines whether or not the data is empty
	 * @access public
	 * @name Variant::isEmpty()
	 * @return bool
	 */
	public function isEmpty() : bool
	{
		// Check the type
		if ($this->mInstanceTypes->linearSearch($this->getType()) !== -1) {
			// We're done
			return $this->mData->isEmpty();
		}
		// Return the empty status
		return empty($this->mData);
	}

	/**
	 * This method determines whether or not the data is null
	 * @access public
	 * @name Variant::isNull()
	 * @return bool
	 */
	public function isNull() : bool
	{
		// Check the type
		if ($this->mInstanceTypes->linearSearch($this->getType()) !== -1) {
			// We're done
			return $this->mData->isEmpty();
		}
		// Return the empty status
		return is_null($this->mData);
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Converters //////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method converts the data to an array
	 * @access public
	 * @name Variant::toArray()
	 * @return array
	 */
	public function toArray() : array
	{
		// Return the array conversion
		return $this->convert(Type::VArray);
	}

	/**
	 * This method converts the data to a boolean
	 * @access public
	 * @name Variant::toBool()
	 * @return bool
	 */
	public function toBool() : bool
	{
		// Return the boolean conversion
		return $this->convert(Type::VBoolean);
	}

	/**
	 * This method convers the data to a double
	 * @access public
	 * @name Variant::toDouble()
	 * @return double
	 */
	public function toDouble() : double
	{
		// Return the double conversion
		return $this->convert(Type::VDouble);
	}

	/**
	 * This method converts the data to a float
	 * @access public
	 * @name Variant::toFloat()
	 * @return float
	 */
	public function toFloat() : float
	{
		// Return the float conversion
		return $this->convert(Type::VFloat);
	}

	/**
	 * This method converts the data to an integer
	 * @access public
	 * @name Variant::toInt()
	 * @return int
	 */
	public function toInt() : int
	{
		// Return the integer conversion
		return $this->convert(Type::VInteger);
	}

	/**
	 * This method converts the data to json
	 * @access public
	 * @name Variant::toJson()
	 * @return string
	 */
	public function toJson() : string
	{
		// Return the json conversion
		return $this->convert(Type::VJson);
	}

	/**
	 * This method converts the data to a map
	 * @access public
	 * @name Variant::toMap()
	 * @return HH\Map
	 */
	public function toMap() : HH\Map
	{
		// Return the map conversion
		return $this->convert(Type::VMap);
	}

	/**
	 * This method converts the data to an escaped MySQL compliant string
	 * @access public
	 * @name Variant::toMySqlString()
	 * @return string
	 */
	public function toMySqlString() : string
	{
		// Grab the string
		$strData = $this->convert(Type::VString);
		// Check for null
		if (is_null($strData)) {
			// Return a plain null
			return 'NULL';
		}
		// Return the quoted string
		return "'".addslashes($strData)."'";
	}

	/**
	 * This method converts the data to a quoted MySQL compliant string list
	 * @access public
 	 * @name Variant::toMySqlStringList()
	 * @param string $strDelimiter [,]
	 * @return string
	 */
	public function toMySqlStringList(string $strDelimiter = ',') : string
	{
		// Check for an array
		if (is_array($this->mData)) {
			// Create the vector
			$vecData = new Vector($this->mData);
		} else {
			// Create the vector
			$vecData = $this->mData;
		}
		// Check the type
		if ($vecData instanceof HH\Vector) {
			// Create a temporary vector
			$vecTemp = Vector {};
			// Iterate over the data
			foreach ($vecData->getIterator() as $mixData) {
				// Set the data into the temporary vector
				$vecTemp
					->add(Variant::Factory($mixData)->toMySqlString());
			}
			// Return the string list
			return implode($strDelimiter, $vecTemp->toArray());
		}
		// Return a MySQL null
		return 'NULL';
	}

	/**
	 * This method converts the data to a null type
	 * @access public
	 * @name Variant::toNull()
	 * @return null
	 */
	public function toNull() : null
	{
		// Return the null conversion
		return $this->convert(Type::VNull);
	}

	/**
	 * This method converts the data to an object
	 * @access public
	 * @name Variant::toObject()
	 * @return object
	 */
	public function toObject() : object
	{
		// Return the object conversion
		return $this->convert(Type::VObject);
	}

	/**
	 * This method converts the data to a pair
	 * @access public
	 * @name Variant::toPair()
	 * @return HH\Pair
	 */
	public function toPair() : HH\Pair
	{
		// Return the pair conversion
		return $this->convert(Type::VPair);
	}

	/**
	 * This method converts the data to a set
	 * @access public
	 * @name Variant::toSet()
	 * @return HH\Set
	 */
	public function toSet() : HH\Set
	{
		// Return the set conversion
		return $this->convert(Type::VSet);
	}

	/**
	 * This method converts the data to a string
	 * @access public
	 * @name Variant::toString()
	 * @return string
	 */
	public function toString() : string
	{
		// Return the string conversion
		return $this->convert(Type::VString);
	}

	/**
	 * This method converts a vector or array to a string list
	 * @access public
	 * @name Variant::toStringList()
	 * @param string $strDelimiter [,]
	 * @return string
	 */
	public function toStringList(string $strDelimiter = ',') : string
	{
		// Check for an array
		if (is_array($this->mData)) {
			// Set the data
			$vecData = new Vector($this->mData);
		} else {
			// Set the data
			$vecData = $this->mData;
		}
		// Check the type
		if ($vecData instanceof HH\Vector) {
			// Create a temporary vector
			$vecTemp = Vector {};
			// Iterate over the data
			foreach ($vecData->getIterator() as $mixData) {
				// Set the string into the vector
				$vecTemp
					->add(Variant::Factory($mixData)->toString());
			}
			// Return the string list
			return implode($strDelimiter, $vecTemp->toArray());
		}
		// Return an empty string
		return '';
	}

	/**
	 * This method converts the data to a vector
	 * @access public
	 * @name Variant::toVector()
	 * @return HH\Vector
	 */
	public function toVector() : HH\Vector
	{
		// Return the vector conversion
		return $this->convert(Type::VVector);
	}

	/**
	 * This method explodes a string into a vector of strings
	 * @access public
	 * @name Variant::toVectorList()
	 * @param string $strDelimiter [,]
	 * @param int $intLimit [null]
	 * @return HH\Vector<string>
	 */
	public function toVectorList(string $strDelimiter = ',', ?int $intLimit = null) : Vector<string>
	{
		// Make sure we have a string
		if (is_string($this->mData)) {
			// Return the exploded vector
			return new Vector(explode($strDelimiter, $this->mData, $intLimit));
		}
		// Return an empty vector
		return Vector {};
	}

	//////////////////////////////////////////////////////////////////////////////
	/// Getters /////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	/**
	 * This method returns the original data as it was constructed into this class
	 * @access public
	 * @name Variant::getData()
	 * @return mixed Variant::$mData
	 */
	public function getData() : mixed
	{
		// Return the original data
		return $this->mData;
	}

	/**
	 * This method returns the actual type of the data
	 * @access public
	 * @name Variant::getType()
	 * @return Type
	 */
	public function getType() : ?Type
	{
		// Get the type
		$strType = gettype($this->mData);
		// Check for an object
		if (($strType === Type::VObject) && ($this->mInstanceTypes->linearSearch($strType) == -1)) {
			// Return the actual type
			return $this->mInstanceTypes->get($this->mInstanceTypes->linearSearch($strType));
		/* } elseif (is_callable($this->mData)) {
			// Return the actual type
			return Type::VCallable; */
		} elseif (is_object(json_decode($this->mData))) {
			// Return the actual type
			return Type::VJson;
		} else {
			// Return the type
			return $strType;
		}
	}

	/**
	 * This method is for VariantMap and VariantList
	 * @access public
	 * @name Variant::getVariantData()
	 * @return VariantList|VariantMap Variant::$mData
	 */
	public function getVariantData() : Variant
	{
		// Return the data as-is
		return $this->mData;
	}
}
