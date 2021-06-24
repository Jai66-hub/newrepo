

enum {

	RegistrationAcceptGUTI5GType                                   = 0x77
	RegistrationAcceptEquivalentPlmnsType                          = 0x4A
	RegistrationAcceptTAIListType                                  = 0x54
	RegistrationAcceptAllowedNSSAIType                             = 0x15
	RegistrationAcceptRejectedNSSAIType                            = 0x11
	RegistrationAcceptConfiguredNSSAIType                          = 0x31
	RegistrationAcceptNetworkFeatureSupport5GSType                 = 0x21
	RegistrationAcceptPDUSessionStatusType                         = 0x50
	RegistrationAcceptPDUSessionReactivationResultType             = 0x26
	RegistrationAcceptPDUSessionReactivationResultErrorCauseType   = 0x72
	RegistrationAcceptLADNInformationType                          = 0x79
	RegistrationAcceptMICOIndicationType                           = 0x0B
	RegistrationAcceptNetworkSlicingIndicationType                 = 0x09
	RegistrationAcceptServiceAreaListType                          = 0x27
	RegistrationAcceptT3512ValueType                               = 0x5E
	RegistrationAcceptNon3GppDeregistrationTimerValueType          = 0x5D
	RegistrationAcceptT3502ValueType                               = 0x16
	RegistrationAcceptEmergencyNumberListType                      = 0x34
	RegistrationAcceptExtendedEmergencyNumberListType              = 0x7A
	RegistrationAcceptSORTransparentContainerType                  = 0x73
	RegistrationAcceptEAPMessageType                               = 0x78
	RegistrationAcceptNSSAIInclusionModeType                       = 0x0A
	RegistrationAcceptOperatordefinedAccessCategoryDefinitionsType = 0x76
	RegistrationAcceptNegotiatedDRXParametersType                  = 0x51

}

void Decode

func (a *RegistrationAccept) DecodeRegistrationAccept(byteArray *[]byte) {
	buffer := bytes.NewBuffer(*byteArray)
	binary.Read(buffer, binary.BigEndian, &a.ExtendedProtocolDiscriminator.Octet)
	binary.Read(buffer, binary.BigEndian, &a.SpareHalfOctetAndSecurityHeaderType.Octet)
	binary.Read(buffer, binary.BigEndian, &a.RegistrationAcceptMessageIdentity.Octet)
	binary.Read(buffer, binary.BigEndian, &a.RegistrationResult5GS.Len)
	a.RegistrationResult5GS.SetLen(a.RegistrationResult5GS.GetLen())
	binary.Read(buffer, binary.BigEndian, &a.RegistrationResult5GS.Octet)
	for buffer.Len() > 0 {
		var ieiN uint8
		var tmpIeiN uint8
		binary.Read(buffer, binary.BigEndian, &ieiN)
		// fmt.Println(ieiN)
		if ieiN >= 0x80 {
			tmpIeiN = (ieiN & 0xf0) >> 4
		} else {
			tmpIeiN = ieiN
		}
		// fmt.Println("type", tmpIeiN)
		switch tmpIeiN {
		case RegistrationAcceptGUTI5GType:
			a.GUTI5G = nasType.NewGUTI5G(ieiN)
			binary.Read(buffer, binary.BigEndian, &a.GUTI5G.Len)
			a.GUTI5G.SetLen(a.GUTI5G.GetLen())
			binary.Read(buffer, binary.BigEndian, a.GUTI5G.Octet[:a.GUTI5G.GetLen()])

		default:
		}
	}
}