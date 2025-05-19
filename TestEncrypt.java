package baiTapLonATBMTT;

import java.util.HashMap;
import java.util.List;

public class TestEncrypt {
	public static boolean checkKey(String key) {
		return key.length() == 8;
	}

	public static String permute(String k, int[] arr, int n) {
		StringBuilder per = new StringBuilder();

		for (int i = 0; i < n; i++) {
			per.append(k.charAt(arr[i] - 1));
		}

		return per.toString();
	}

	public static String shiftLeft(String k, int shifts) {
		for (int i = 0; i < shifts; i++) {
			// Dịch trái 1 lần: lấy từ ký tự thứ 1 đến 27, sau đó nối ký tự đầu vào cuối
			String s = k.substring(1, 28) + k.charAt(0);
			k = s;
		}
		return k;
	}

	public static String getXor(String a, String b) {
		StringBuilder ans = new StringBuilder();

		// Kiểm tra độ dài chuỗi để tránh lỗi
		if (a.length() != b.length()) {
			return ""; // hoặc ném ra ngoại lệ tùy bạn
		}

		for (int i = 0; i < a.length(); i++) {
			if (a.charAt(i) == b.charAt(i)) {
				ans.append('0');
			} else {
				ans.append('1');
			}
		}

		return ans.toString();
	}

	public static String hex2bin(String s) {
		HashMap<Character, String> map = new HashMap<>();

		map.put('0', "0000");
		map.put('1', "0001");
		map.put('2', "0010");
		map.put('3', "0011");
		map.put('4', "0100");
		map.put('5', "0101");
		map.put('6', "0110");
		map.put('7', "0111");
		map.put('8', "1000");
		map.put('9', "1001");
		map.put('A', "1010");
		map.put('B', "1011");
		map.put('C', "1100");
		map.put('D', "1101");
		map.put('E', "1110");
		map.put('F', "1111");

		StringBuilder bin = new StringBuilder();

		for (int i = 0; i < s.length(); i++) {
			char c = Character.toUpperCase(s.charAt(i)); // đảm bảo chữ thường cũng được xử lý
			if (map.containsKey(c)) {
				bin.append(map.get(c));
			} else {
				throw new IllegalArgumentException("Ký tự không hợp lệ trong chuỗi hex: " + c);
			}
		}

		return bin.toString();
	}

	static String bin2hex(String s) {
		HashMap<String, String> mp = new HashMap<>();
		mp.put("0000", "0");
		mp.put("0001", "1");
		mp.put("0010", "2");
		mp.put("0011", "3");
		mp.put("0100", "4");
		mp.put("0101", "5");
		mp.put("0110", "6");
		mp.put("0111", "7");
		mp.put("1000", "8");
		mp.put("1001", "9");
		mp.put("1010", "A");
		mp.put("1011", "B");
		mp.put("1100", "C");
		mp.put("1101", "D");
		mp.put("1110", "E");
		mp.put("1111", "F");

		StringBuilder hex = new StringBuilder();
		for (int i = 0; i < s.length(); i += 4) {
			String ch = s.substring(i, i + 4);
			hex.append(mp.get(ch));
		}
		return hex.toString();
	}

	public String encrypt(String pt, List<String> rkb, List<String> rk) {
		// Initial Permutation Table
		int[] initialPerm = { 58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14,
				6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53,
				45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7 };

		// Expansion D-box Table
		int[] expD = { 32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18,
				19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };

		// Straight Permutation Table
		int[] per = { 16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13,
				30, 6, 22, 11, 4, 25 };

		// Final Permutation Table
		int[] finalPerm = { 40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30,
				37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42,
				10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25 };

		// S-boxes
		int[][][] s = {
				{ { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
						{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
						{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
						{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 } },
				{ { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
						{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
						{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
						{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 } },
				{ { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
						{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
						{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
						{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 } },
				{ { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
						{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
						{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
						{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 } },
				{ { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
						{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
						{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
						{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 } },
				{ { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
						{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
						{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
						{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 } },
				{ { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
						{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
						{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
						{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 } },
				{ { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
						{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
						{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
						{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } } };

		String bin = hex2bin(pt);
		bin = permute(bin, initialPerm, 64);

		String left = bin.substring(0, 31);
		String right = bin.substring(32, 63);

		for (int i = 0; i < 16; i++) {
			String rightExpanded = permute(right, expD, 48);
			String x = getXor(rkb.get(i), rightExpanded);
			StringBuilder op = new StringBuilder();

			for (int j = 0; j < 8; j++) {
				String chunk = x.substring(j * 6, j * 6 + 6);
				int row = Integer.parseInt("" + chunk.charAt(0) + chunk.charAt(5), 2);
				int col = Integer.parseInt(chunk.substring(1, 5), 2);
				int val = s[j][row][col];
				op.append(String.format("%4s", Integer.toBinaryString(val)).replace(' ', '0'));
			}

			op = new StringBuilder(permute(op.toString(), per, 32));
			String xLeft = getXor(op.toString(), left);
			left = right;
			right = xLeft;

			// Swap only if not last round
			if (i != 15) {
				String temp = left;
				left = right;
				right = temp;
			}
		}

		String combine = left + right;
		String cipher = bin2hex(permute(combine, finalPerm, 64));
		return cipher;
	}

	public static void main(String[] args) {

	}
}
