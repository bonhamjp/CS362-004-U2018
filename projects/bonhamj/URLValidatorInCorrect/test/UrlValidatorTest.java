import junit.framework.TestCase;

//Needed for error collector
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ErrorCollector;
import org.hamcrest.CoreMatchers;

// Needed for assert
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
//Again, it is up to you to use this file or not!

public class UrlValidatorTest {

	// Use error collector to not let assert calls stop tests. Code and usage was
	// adapted from:
	// https://stackoverflow.com/questions/10221891/continuing-test-execution-in-junit4-even-when-one-of-the-asserts-fails
	// https://junit.org/junit4/javadoc/latest/org/junit/rules/ErrorCollector.html
	// https://stackoverflow.com/questions/31443474/why-my-junit-error-collector-is-not-reporting-the-error
	@Rule
	public ErrorCollector collector = new ErrorCollector();


   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */

   @Test
   public void testManualTest()
   {
	   //You can use this function to implement your manual testing

	   //Allows all validly formatted schemes to pass validation instead of
	   //supplying a set of valid schemes.
	   long allowAllSchemes = 1;

	   // Set up new URl Validator
	   UrlValidator UV = new UrlValidator(null, null, allowAllSchemes);

	   // Manual tests, check different URLs that are known to be valid/invalid
	   try {
		   collector.checkThat("http://www.google.com", UV.isValid("http://www.google.com"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("http://www.reddit.com:60079", UV.isValid("http://www.reddit.com:60079"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("https://www.amazon.com/gp/css/order-history", UV.isValid("https://www.amazon.com/gp/css/order-history"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("file:///Users/sidharthsengupta/Downloads/Lesson19AgansRules.pdf", UV.isValid("file:///Users/sidharthsengupta/Downloads/Lesson19AgansRules.pdf"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("http://www.canvas.oregonstate.edu:65555", UV.isValid("http://www.canvas.oregonstate.edu:65555"), CoreMatchers.equalTo(false));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("https://www.messenger.com/t/1111111111111", UV.isValid("https://www.messenger.com/t/1111111111111"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("https:/boom", UV.isValid("https:/boom"), CoreMatchers.equalTo(false));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("http://espn.com?some=thing&and=another", UV.isValid("http://espn.com?some=thing&and=another"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("https://espn.com?some=thing&and=another", UV.isValid("https://espn.com?some=thing&and=another"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("ftp://domain.com/file.html", UV.isValid("ftp://domain.com/file.html"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("http://255.255.255.255:1000", UV.isValid("http://255.255.255.255:1000"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("https://256.255.255.255/somefile.txt", UV.isValid("https://256.255.255.255/somefile.txt"), CoreMatchers.equalTo(false));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("123://www.example.org", UV.isValid("123://www.example.org"), CoreMatchers.equalTo(false));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("h123://www.example.org", UV.isValid("h123://www.example.org"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("http://www.test.badTLD", UV.isValid("http://www.test.badTLD"), CoreMatchers.equalTo(false));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("http://www.canvas.oregonstate.edu//assignment5", UV.isValid("http://www.canvas.oregonstate.edu//assignment5"), CoreMatchers.equalTo(false));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("https:123.123.123.123:12345/home.html", UV.isValid("https:123.123.123.123:12345/home.html"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("http:www.manualtesting.edu", UV.isValid("http:www.manualtesting.edu"), CoreMatchers.equalTo(false));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("https://en.wikipedia.org/wiki/Java_(programming_language)", UV.isValid("https://en.wikipedia.org/wiki/Java_(programming_language)"), CoreMatchers.equalTo(true));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }

	   try {
		   collector.checkThat("http://osu-cs.slack.com/...messages/", UV.isValid("https://osu-cs.slack.com/...messages/"), CoreMatchers.equalTo(false));
	   } catch (Throwable t) {
		   collector.addError(t);
	   }
   }

   @Test
   public void testValidUrlPartitions() {
	   // Valid URL partitions
	   UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // valid scheme+authority
	   assertTrue("https://www.youtube.com should be valid", urlValidator.isValid("https://www.youtube.com"));

	   // valid scheme+authority+port
	   assertTrue("https://www.google.com:8000 should be valid", urlValidator.isValid("https://www.google.com:8000"));

	   // valid scheme+authority+path
	   assertTrue("http://www.tumblr.com/dashboard should be valid", urlValidator.isValid("http://www.tumblr.com/dashboard"));

	   // valid scheme+authority+port+path
	   assertTrue("http://www.canvas.oregonstate.edu:4563/courses/1683590 should be valid", urlValidator.isValid("http://www.canvas.oregonstate.edu:4563/courses/1683590"));

	   // valid scheme+authority+path+query
	   assertTrue("https://www.reddit.com/r/OSUOnlineCS/search?q=funny&restrict_sr=1 should be valid", urlValidator.isValid("https://www.reddit.com/r/OSUOnlineCS/search?q=funny&restrict_sr=1"));

	   // valid scheme+authority+port+path+query
	   assertTrue("ftp://www.foodnetwork.com:9034/search?t=dessert should be valid", urlValidator.isValid("ftp://www.foodnetwork.com:9034/search?t=dessert"));
   }

   @Test
   public void testInvalidUrlPartitions(){
	   // Invalid URL partitions
	   UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // invalid invalid order (e.g. query+scheme+authority)
	   assertFalse("?name=Zachhttp://www.youtube.com should be invalid", urlValidator.isValid("?name=Zachhttp://www.youtube.com"));

	   // invalid scheme
	   assertFalse("123://www.tumblr.com/dashboard should be invalid", urlValidator.isValid("123://www.tumblr.com/dashboard"));

	   // invalid authority
	   assertFalse("https://256.254.765.255/charlie should be invalid", urlValidator.isValid("https://256.254.765.255/charlie"));

	   // invalid port
	   assertFalse("https://www.google.com:-500 should be invalid", urlValidator.isValid("https://www.google.com:-500"));

	   // invalid path
	   assertFalse("http://www.canvas.oregonstate.edu//courses/1683590 should be invalid", urlValidator.isValid("http://www.canvas.oregonstate.edu//courses/1683590"));

	   // invalid query
	   assertFalse("https://www.reddit.com/r/OSUOnlineCS/search? q=funny&restrict_sr=1 should be invalid", urlValidator.isValid("https://www.reddit.com/r/OSUOnlineCS/search? q=funny=&restrict_sr=1"));

	   // invalid - valid scheme only
	   assertFalse("https:// should be invalid", urlValidator.isValid("https://"));

	   // invalid - valid authority only
	   assertFalse("www.youtube.com should be invalid", urlValidator.isValid("www.youtube.com"));

	   // invalid - valid port only
	   assertFalse(":8354 should be invalid", urlValidator.isValid(":8354"));

	   // invalid - valid path only
	   assertFalse("/turkey_recipes/thanksgiving", urlValidator.isValid("/turkey_recipes/thanksgiving"));

	   // invalid - valid query only
	   assertFalse("?name=zach&cs_major=true", urlValidator.isValid("?name=zach&cs_major=true"));

	   // invalid - empty string
	   assertFalse("\"\" (empty string) should be invalid", urlValidator.isValid(""));

	   // invalid - null
	   assertFalse("null should be invalid", urlValidator.isValid(null));
   }

   @Test
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   // URL scheme test components
	   String[] testUrlSchemeComponents = { "https://", "x//", "http://" };
	   boolean[] testUrlSchemeComponentsIsValid = { true, false, true };

	   // URL authority test components
	   String[] testUrlAuthorityComponents = { "256.255.255.255", "www.oregonstate.edu" };
	   boolean[] testUrlAuthorityComponentsIsValid = { false, true };

	   // URL port test components
	   String[] testUrlPortComponents = { ":3000", "-3000" };
	   boolean[] testUrlPortComponentsIsValid = { true, false };

	   // URL path test components
	   String[] testUrlPathComponents = { "/a_path", "../" };
	   boolean[] testUrlPathComponentIsValid = { true, false };

	   // URL options test components
	   String[] testUrlOptionsComponents = { "//", "/another/path" };
	   boolean[] testUrlOptionsComponentIsValid = { false, true };

	   // URL query test components
	   String[] testUrlQueryComponents = { "?name=john", "?class=osu322&grade=A" };
	   boolean[] testUrlQueryComponentsIsValid = { true, true };

	   // setup url validator
	   UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // build every combination of components
	   for(int i = 0;i < testUrlSchemeComponents.length;i++) {
		   for(int j = 0;j < testUrlAuthorityComponents.length;j++) {
			   for(int k = 0;k < testUrlPortComponents.length;k++) {
				   for(int l = 0;l < testUrlPathComponents.length;l++) {
					   for(int m = 0;m < testUrlOptionsComponents.length;m++) {
						   for(int n = 0;n < testUrlQueryComponents.length;n++) {
							   StringBuilder urlBuffer = new StringBuilder();

	                           // combine each url component
	                           urlBuffer.append(testUrlSchemeComponents[i]);
	                           urlBuffer.append(testUrlAuthorityComponents[j]);
	                           urlBuffer.append(testUrlPortComponents[k]);
	                           urlBuffer.append(testUrlPathComponents[l]);
	                           urlBuffer.append(testUrlOptionsComponents[m]);
	                           urlBuffer.append(testUrlQueryComponents[n]);

	                           String urlString = urlBuffer.toString();
	                           boolean urlIsValid = testUrlSchemeComponentsIsValid[i] &&
	                                                testUrlAuthorityComponentsIsValid[j] &&
	                                                testUrlPortComponentsIsValid[k] &&
	                                                testUrlPathComponentIsValid[l] &&
	                                                testUrlOptionsComponentIsValid[m] &&
	                                                testUrlQueryComponentsIsValid[n];

	                           boolean result = urlValidator.isValid(urlString);

	                           // print if valid url
	                           if(urlIsValid == true) {
	                        	   System.out.println(urlString);
	                           }

	                           // assert url validity matches urlValidator output
	                           assertEquals(urlString, urlIsValid, result);
	                        }
	                    }
	                }
	            }
	        }
	    }
   }

   public static void main() {

	  UrlValidatorTest fct = new UrlValidatorTest();
	  fct.testManualTest();
	  fct.testValidUrlPartitions();
	  fct.testInvalidUrlPartitions();
	  fct.testIsValid();

   }

}
